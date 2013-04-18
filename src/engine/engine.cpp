#include "engine/engine.hpp"

namespace qrw
{
	Engine::Engine()
	:	board(0),
		status(EES_UNDEFINED)
	{}

	Engine::~Engine()
	{}
 
 	void Engine::init(int x, int y)
 	{}

 	Player& Engine::getCurrentPlayer()
 	{
 		return players[currentplayer];
 	}

 	Player& Engine::changePlayer()
 	{
 		currentplayer = (currentplayer + 1) % 2;
 		return getCurrentPlayer();
 	}

	/**
	 * @Return: 0 - success, -1 - wrong player, -2 origin empty,
	 * 			-3 destination not empty, -4 or out of range,
	 *			-5 dest out of ranage
	 */
 	int Engine::moveUnit(int orx, int ory, int destx, int desty)
 	{
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

 		orsquare->setUnit(0);
 		destsquare->setUnit(unit);
 		return 0;
 	}
 }
