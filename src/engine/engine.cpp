#include <stdio.h>

#include "engine/engine.hpp"

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
	{}

	void Engine::init(int boardwidth, int boardheight)
	{
		delete board;
		board = new Board(boardwidth, boardheight);
		currentplayer = 0;
		status = EES_PREPARE;
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
		std::vector<Unit*> playerunits = getCurrentPlayer().getUnits();
		for(std::vector<Unit*>::iterator it = playerunits.begin();
			it != playerunits.end(); ++it)
		{
			(*it)->setCurrentMovement((*it)->getMovement());
		}
		currentplayer = (currentplayer + 1) % 2;
		// return getCurrentPlayer();
	}

	/**
	 * @Return: 0 - success, -1 - wrong player, -2 origin empty,
	 *			-3 on destination is unit of same player, -4 origin out of range,
	 *			-5 dest out of ranage, -6 not enough movement,
	 *			-7 game not running, -8 unit on origin died, -9 enemy unit
	 *			was not defeated, -10 enemy out of range
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

		int distance = orsquare->getDistance(destsquare);
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
			if(srcunit->getHP() == 0)
			{
				orsquare->setUnit(0);
				return -8;
			}
			if(destunit->getHP() > 0)
				return -9;
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
		Unit* unit;
		switch(unittype)
		{
			case EUT_SWORDMAN:  unit = new Unit(EUT_SWORDMAN, 5, 2, 1, 1, 3, player);
								break;
			case EUT_ARCHER:	unit = new Unit(EUT_ARCHER, 5, 2, 1, 3, 2, player);
								break;
			default:			unit = new Unit(EUT_SPEARMAN, 5, 2, 1, 2, 2, player);
								break;
		}
		player->addUnit(unit);
		square->setUnit(unit);
		return true;
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

	Player* Engine::getPlayer(int id)
	{
		if(id == 0 || id == 1)
			return &players[id];
		return 0;
	}
}
