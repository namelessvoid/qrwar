#ifndef QRW_ENGINE_HPP
#define QRW_ENGINE_HPP

#include <map>

#include "engine/board.hpp"
#include "engine/player.hpp"

namespace qrw
{
	enum ENGINSTATES
	{
		EES_UNDEFINED,
		EES_INITED,
		EES_PREPARE,
		EES_RUNNING,
		EES_ENDED
	};

	class Engine
	{
		public:
			Engine();
			~Engine();

			void init(int boardwidth, int boardheight);
			void startGame();

			ENGINSTATES getStatus();

			void createPlayerUnits(int playerid, std::map<UNITTYPES, int> unitcounts);

			Player& getCurrentPlayer();
			void endTurn();

			Board* getBoard();

			/**
			 * This function is used to move a unit during a running game. Not to be confused
			 * with moveUnitDeployment()!
			 *
			 * @Return: 0 - success, -1 - wrong player, -2 origin empty,
			 * 			-3 on destination is unit of same player, -4 or out of range,
			 *			-5 dest out of ranage, -6 not enough movement,
			 *			-7 status != EES_RUNNING, -8 unit on origin died, -9 enemy unit
			 *			was not defeated
			 */
			int moveUnitIngame(int orx, int ory, int destx, int desty);

			/**
			 * This funciton is used to move a unit during deployment phase. Not to be confused
			 * with moveUnitIngame()!
			 *
			 * @return
			 */
			int moveUnitDeployment(int orx, int ory, int destx, int desty);

			/**
			 * Place a unit on the board.
			 * @Return: False if status != EES_PREPRARE, index out of board
			 *          or destination is not empty.
			 */
			bool placeUnit(int x, int y, int playerid, UNITTYPES unittype);

			/**
			 * Place a piece of terrain on the board.
			 * @Return: False if status != EES_PREPARE or index out of board
			 */
			bool placeTerrain(int x, int y, TERRAINTYPES terraintype);

			Player* getPlayer(int id);

		private:
			// void setPlayerUnits(int id, int unitnumbers[EUT_NUMBEROFUNITTYPES]);

			Board* board;
			int currentplayer;
			Player players[2];
			ENGINSTATES status;
	};
}

#endif
