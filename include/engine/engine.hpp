#ifndef QRW_ENGINE_HPP
#define QRW_ENGINE_HPP

#include <map>

#include "engine/terrain.hpp"
#include "engine/unit.hpp"
#include "engine/player.hpp"

namespace qrw
{
	class Board;

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

			int getMaxPlayerUnits();
			void createPlayerUnits(int playerid, std::map<UNITTYPES, int> unitcounts);

			Player& getCurrentPlayer();
			void endTurn();

			Board* getBoard();

			/**
			 * This funciton is used to move a unit during deployment phase. Not to be confused
			 * with moveUnitIngame()!
			 *
			 * @return
			 */
			int moveUnitDeployment(Coordinates origin, Coordinates destination);

			/**
			 * Place a unit on the board.
			 * @Return: False if status != EES_PREPRARE, index out of board
			 *          or destination is not empty.
			 */
			bool placeUnit(Coordinates position, int playerid, UNITTYPES unittype);

			/**
			 * Place a piece of terrain on the board.
			 * @Return: False if status != EES_PREPARE or index out of board
			 */
			bool placeTerrain(Coordinates position, TERRAINTYPES terraintype);

			/**
			 * Remove a piece of terrain on the board.
			 *
			 * @return False if status != EES_PREPARE or index out of board.
			 */
			bool removeTerrain(Coordinates position);

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
