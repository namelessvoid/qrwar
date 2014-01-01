#include <stdio.h>
#include <climits>

#include "engine/engine.hpp"

#include "engine/pathfinding/astar.hpp"
#include "engine/pathfinding/path.hpp"

namespace qrw
{
	Engine::Engine()
	:	board(0),
		status(EES_UNDEFINED)
	{
		players[0].setName("Player The First");
		players[0].setId(0);
		players[1].setName("Player The Second");
		players[1].setId(1);

		pathfinder = new AStar();
	}

	Engine::~Engine()
	{
		delete pathfinder;
	}

	void Engine::init(int boardwidth, int boardheight)
	{
		delete board;
		board = new Board(boardwidth, boardheight);
		pathfinder->setBoard(board);
		currentplayer = 0;
		status = EES_PREPARE;

		int maxarmysize = INT_MAX;
		// int maxarmysize = getMaxPlayerUnits();
		players[0].getArmy().deleteAllUnits();
		players[0].getArmy().setMaxSize(maxarmysize);
		players[1].getArmy().deleteAllUnits();
		players[1].getArmy().setMaxSize(maxarmysize);
	}

	void Engine::startGame()
	{
		currentplayer = 0;
		status = EES_RUNNING;
	}

	ENGINSTATES Engine::getStatus()
	{
		return status;
	}

	int Engine::getMaxPlayerUnits()
	{
		if(board)
			return (board->getHeight() * board->getWidth()) / 3;
		return 0;
	}

	void Engine::createPlayerUnits(int playerid, std::map<UNITTYPES, int> unitcounts)
	{
		Player* player = getPlayer(playerid);
		UNITTYPES unittype;
		Unit* unit;

		for(auto iter = unitcounts.begin(); iter != unitcounts.end(); ++iter)
		{
			unittype = iter->first;
			for(int i = 0; i < iter->second; ++i)
			{
				// Create new unit
				switch(unittype)
				{
					case EUT_SWORDMAN:
						unit = new Unit(EUT_SWORDMAN, 5, 2, 1, 1, 3, player);
						break;

					case EUT_ARCHER:
						unit = new Unit(EUT_ARCHER, 5, 2, 1, 3, 2, player);
						break;

					default:
						unit = new Unit(EUT_SPEARMAN, 5, 2, 1, 2, 2, player);
						break;
				}
				// Add new unit to army
				player->getArmy().addUnit(unit);
			}
		}
	}

	// bool Engine::setUnits(int playeroneunits[EUT_NUMBEROFUNITTYPES],
		// int playertwounits[EUT_NUMBEROFUNITTYPES])
	// {
	//	players[0].clearUnits();
	//	players[1].clearUnits();

	//	if(status != EES_PREPARE)
	//		return false;
	//	setPlayerUnits(0, playeroneunits);
	//	setPlayerUnits(1, playertwounits);
	//	return true;
	// }

	// void Engine::setPlayerUnits(int id, int unitnumbers[EUT_NUMBEROFUNITTYPES])
	// {
	//	Player* player = getPlayer(id);
	//	int i;
	//	// Attention! player is "overwritten" in the method Player::addUnit(...).
	//	for(i = 0; i < unitnumbers[EUT_SWORDMAN]; ++i)
	//		player->addUnit(new Unit(EUT_SWORDMAN, 2, 1, 1, 3, player));
	//	for(i = 0; i < unitnumbers[EUT_ARCHER]; ++i)
	//		player->addUnit(new Unit(EUT_ARCHER, 2, 1, 3, 2, player));
	//	for(i = 0; i < unitnumbers[EUT_SPEARMAN]; ++i)
	//		player->addUnit(new Unit(EUT_SPEARMAN, 2, 1, 2, 2, player));
	// }

	Board* Engine::getBoard()
	{
		return board;
	}

	Player& Engine::getCurrentPlayer()
	{
		return players[currentplayer];
	}

	void Engine::endTurn()
	{
		// Reset movement of current players units.
		Army& army = getCurrentPlayer().getArmy();

		for(int i = 0; i < EUT_NUMBEROFUNITTYPES; ++i)
		{
			std::set<Unit*>& unitset = army.getUnitsByType((UNITTYPES)i);

			for(auto iter = unitset.begin(); iter != unitset.end(); ++iter)
				(*iter)->setCurrentMovement((*iter)->getMovement());
		}

		currentplayer = (currentplayer + 1) % 2;
	}

	/**
	 * @Return: 0 - success, -1 - wrong player, -2 origin empty,
	 *			-3 on destination is unit of same player, -4 origin out of range,
	 *			-5 dest out of ranage, -6 not enough movement,
	 *			-7 game not running, -8 unit on origin died, -9 enemy unit
	 *			was not defeated, -10 enemy out of range, -11 defender died
	 */
	int Engine::moveUnitIngame(int orx, int ory, int destx, int desty)
	{
		// Game is not running
		if(status != EES_RUNNING)
			return -7;

		Square* orsquare = board->getSquare(orx, ory);
		// index out of range
		if(orsquare == 0)
			return -4;
		// no unit on this square
		if(orsquare->getUnit() == 0)
			return -2;

		Square* destsquare = board->getSquare(destx, desty);
		// index out of range
		if(destsquare == 0)
			return -5;

		Unit* srcunit = orsquare->getUnit();
				// Unit does not belong to current player
		if(srcunit->getPlayer() != &getCurrentPlayer())
			return -1;

		Path* path = pathfinder->findPath(orsquare->getCoordinates(), destsquare->getCoordinates());
		if(path == 0)
		{
			delete path;
			return -5;
		}

		int distance = path->getMovementCosts();
		delete path;

		// Distance is too far
		if(distance > srcunit->getCurrentMovement())
			return -6;

		// Is there a unit on the destination?
		Unit* destunit = destsquare->getUnit();
		if(destunit != 0)
		{
			// unit on destination belongs to same player
			if(destunit->getPlayer() == srcunit->getPlayer())
				return -3;
			// otherwise: battle

			// Check for range
			printf("distance: %d", distance);
			if(distance > srcunit->getRange())
				return -10;

			// get modificators
			int attackmods[] = {0, 0};
			int defensemods[] = {0, 0};
			if(orsquare->getTerrain() != NULL)
			{
				attackmods[0] = orsquare->getTerrain()->getModificators()[0];
				attackmods[1] = orsquare->getTerrain()->getModificators()[1];
			}
			if(destsquare->getTerrain() != NULL)
			{
				defensemods[0] = destsquare->getTerrain()->getModificators()[0];
				defensemods[1] = destsquare->getTerrain()->getModificators()[1];
			}

			srcunit->attack(destunit, attackmods, defensemods);
			srcunit->setCurrentMovement(0);
			// Attacker died
			if(srcunit->getHP() == 0)
			{
				orsquare->setUnit(0);
				return -8;
			}
			// No one died
			else if(destunit->getHP() > 0)
			{
				return -9;
			}
			// Defender died
			else
			{
				orsquare->setUnit(0);
				destsquare->setUnit(srcunit);
				return -11;
			}
		}

		srcunit->setCurrentMovement(srcunit->getCurrentMovement() - distance);
		orsquare->setUnit(0);
		destsquare->setUnit(srcunit);
		return 0;
	}

	int Engine::moveUnitDeployment(int orx, int ory, int destx, int desty)
	{
		Square* orsquare = board->getSquare(orx, ory);
		if(orsquare->getUnit() == NULL)
			return -1;

		Square* destsquare = board->getSquare(destx, desty);

		if(destsquare->getUnit() != NULL)
			return -1;

		destsquare->setUnit(orsquare->getUnit());
		orsquare->setUnit(NULL);
		return 0;
	}

	bool Engine::placeUnit(int x, int y, int playerid, UNITTYPES unittype)
	{
		if(status != EES_PREPARE)
			return false;
		Square* square = board->getSquare(x, y);

		if(square == 0)
			return false;

		if(square->getUnit() != 0)
			return false;

		Player* player = getPlayer(playerid);
		Unit* unit = *(player->getArmy().getUndeployedUnitsByType(unittype).begin());
		if(unit)
		{
			player->getArmy().markUnitAsDeployed(unit);
			square->setUnit(unit);
			return true;
		}
		return false;
	}

	bool Engine::placeTerrain(int x, int y, TERRAINTYPES terraintype)
	{
		if(status != EES_PREPARE)
			return false;
		Square* square = board->getSquare(x, y);
		if(square == NULL)
			return false;

		if(square->getTerrain() != NULL)
			delete square->getTerrain();
		Terrain* terrain;
		switch(terraintype)
		{
			case ET_WOOD:	terrain = new Terrain(ET_WOOD, -1, 1);
							break;
			case ET_HILL:	terrain = new Terrain(ET_HILL, 1, -1);
							break;
			default:		terrain = new Terrain(ET_WALL, 1, 1);
							break;
		}
		square->setTerrain(terrain);
		return true;
	}

	bool Engine::removeTerrain(int x, int y)
	{
		if(status != EES_PREPARE)
			return false;

		Square* square = board->getSquare(x, y);
		if(square == NULL)
			return false;

		if(square->getTerrain())
			delete square->getTerrain();
		square->setTerrain(NULL);
	}

	Player* Engine::getPlayer(int id)
	{
		if(id == 0 || id == 1)
			return &players[id];
		return 0;
	}
}
