#include <stdio.h>
#include <climits>

#include "engine/engine.hpp"
#include "engine/board.hpp"
#include "engine/square.hpp"
#include "engine/unit.hpp"
#include "engine/terrain.hpp"

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
	}

	Engine::~Engine()
	{
	}

	void Engine::init(int boardwidth, int boardheight)
	{
		delete board;
		board = new Board(boardwidth, boardheight);
		currentplayer = 0;
		getCurrentPlayer().setActive(true);
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
						unit = new Unit(EUT_SWORDMAN, 5, 2, 1, 1, 3, player, board);
						break;

					case EUT_ARCHER:
						unit = new Unit(EUT_ARCHER, 5, 2, 1, 3, 2, player, board);
						break;

					default:
						unit = new Unit(EUT_SPEARMAN, 5, 2, 1, 2, 2, player, board);
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

		// change player and update active flags.
		getCurrentPlayer().setActive(false);
		currentplayer = (currentplayer + 1) % 2;
		getCurrentPlayer().setActive(true);
	}

	int Engine::moveUnitDeployment(Coordinates origin, Coordinates destination)
	{
		Square* orsquare = board->getSquare(origin);
		if(orsquare->getUnit() == NULL)
			return -1;

		Square* destsquare = board->getSquare(destination);

		if(destsquare->getUnit() != NULL)
			return -1;

		destsquare->setUnit(orsquare->getUnit());
		orsquare->setUnit(NULL);
		return 0;
	}

	bool Engine::placeUnit(Coordinates position, int playerid, UNITTYPES unittype)
	{
		if(status != EES_PREPARE)
			return false;
		Square* square = board->getSquare(position);

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
			unit->setSquare(square);
			return true;
		}
		return false;
	}

	bool Engine::placeTerrain(Coordinates position, TERRAINTYPES terraintype)
	{
		if(status != EES_PREPARE)
			return false;
		Square* square = board->getSquare(position);
		if(square == NULL)
			return false;

		Terrain::Ptr terrain = Terrain::createTerrain(terraintype);
		square->setTerrain(terrain);
		return true;
	}

	bool Engine::removeTerrain(Coordinates position)
	{
		if(status != EES_PREPARE)
			return false;

		Square* square = board->getSquare(position);
		if(square == NULL)
			return false;

		square->setTerrain(NULL);
		return true;
	}

	Player* Engine::getPlayer(int id)
	{
		if(id == 0 || id == 1)
			return &players[id];
		return 0;
	}
}
