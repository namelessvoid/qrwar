#include <stdio.h>

#include "engine/engine.hpp"

namespace qrw
{
	Engine::Engine()
	:	board(0),
		status(EES_UNDEFINED)
	{
		players[0].setName("Player The First");
		players[1].setName("Player The Second");
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

 	bool Engine::setUnits(int playeroneunits[EUT_NUMBEROFUNITTYPES],
		int playertwounits[EUT_NUMBEROFUNITTYPES])
 	{
 		if(status != EES_PREPARE)
 			return false;
 		setPlayerUnits(0, playeroneunits);
 		setPlayerUnits(1, playertwounits);
 		return true;
 	}

 	void Engine::setPlayerUnits(int id, int unitnumbers[EUT_NUMBEROFUNITTYPES])
 	{
 		Player* player = getPlayer(id);
 		std::vector<Unit*> units = player->getUnits();
 		int i;
 		for(i = 0; i < unitnumbers[EUT_SWORDMAN]; ++i)
 			units.push_back(new Unit(EUT_SWORDMAN, 2, 1, 1, 3, player));
 		for(i = 0; i < unitnumbers[EUT_ARCHER]; ++i)
 			units.push_back(new Unit(EUT_ARCHER, 2, 1, 3, 2, player));
 		for(i = 0; i < unitnumbers[EUT_SPEARMAN]; ++i)
 			units.push_back(new Unit(EUT_SPEARMAN, 2, 1, 2, 2, player));
 	}

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
 		currentplayer = (currentplayer + 1) % 2;
 		// return getCurrentPlayer();
 	}

	/**
	 * @Return: 0 - success, -1 - wrong player, -2 origin empty,
	 * 			-3 destination not empty, -4 or out of range,
	 *			-5 dest out of ranage, -6 not enough movement,
	 *			-7 game not running
	 */
 	int Engine::moveUnit(int orx, int ory, int destx, int desty)
 	{
 		if(status != EES_RUNNING)
 			return -7;

 		Square* orsquare = board->getSquare(orx, ory);
 		if(orsquare == 0)
 			return -4;
 		if(orsquare->getUnit() == 0)
 			return -2;

 		Square* destsquare = board->getSquare(destx, desty);
 		if(destsquare == 0)
 			return -5;
 		if(destsquare->getUnit() != 0)
 			return -3;

 		Unit *unit = orsquare->getUnit();
 		if(unit->getPlayer() != &getCurrentPlayer())
 			return -1;

 		int distance = orsquare->getDistance(destsquare);
 		if(distance > unit->getCurrentMovement())
 			return -6;

 		unit->setCurrentMovement(unit->getCurrentMovement() - distance);
 		orsquare->setUnit(0);
 		destsquare->setUnit(unit);
 		return 0;
 	}

 	bool Engine::placeUnit(int x, int y, Unit* unit)
 	{
 		if(status != EES_PREPARE)
 			return false;
 		Square* square = board->getSquare(x, y);

 		if(square == 0)
 			return false;

 		if(square->getUnit() != 0)
 			return false;

 		square->setUnit(unit);
 		return true;
 	}

 	Player* Engine::getPlayer(int id)
 	{
 		if(id == 0 || id == 1)
 			return &players[id];
 		return 0;
 	}
 }
