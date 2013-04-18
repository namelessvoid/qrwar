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

			Player& getCurrentPlayer();
			Player& changePlayer();

			/**
			 * @Return: 0 - success, -1 - wrong player, -2 origin empty,
			 * 			-3 destination not empty, -4 or out of range,
			 *			-5 dest out of ranage
			 */
			int moveUnit(int orx, int ory, int destx, int desty);

		private:
			Board* board;
			int currentplayer;
			Player players[2];
			ENGINSTATES status;
	};
}

#endif