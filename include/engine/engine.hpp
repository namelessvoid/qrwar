#ifndef QRW_ENGINE_HPP
#define QRW_ENGINE_HPP

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
			
			// bool setUnits(int playeornoeunits[EUT_NUMBEROFUNITTYPES],
			// 	int playertwounits[EUT_NUMBEROFUNITTYPES]);

			Player& getCurrentPlayer();
			void endTurn();

			Board* getBoard();

			/**
			 * @Return: 0 - success, -1 - wrong player, -2 origin empty,
			 * 			-3 destination not empty, -4 or out of range,
			 *			-5 dest out of ranage, -6 not enough movement,
			 *			-7 status != EES_RUNNING
			 */
			int moveUnit(int orx, int ory, int destx, int desty);

			/**
			 * Place a unit on the board.
			 * @Return: False if status != EES_PREPRARE
			 */
			bool placeUnit(int x, int y, int playerid, UNITTYPES unittype);

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