#ifndef QRW_ENGINE_HPP
#define QRW_ENGINE_HPP

#include <map>

#include "engine/board.hpp"
#include "engine/player.hpp"

namespace qrw
{
	class AbstractAlgorithm;
	class Path;

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
			 * This function is used to move a unit during a running game. Not to be confused
			 * with moveUnitDeployment()!
			 *
			 * @Return: 0 - success, -1 - wrong player, -2 origin empty,
			 * 			-3 on destination is unit of same player, -4 or out of range,
			 *			-5 dest out of ranage, -6 not enough movement,
			 *			-7 status != EES_RUNNING, -8 unit on origin died, -9 enemy unit
			 *			was not defeated
			 */
			int moveUnitIngame(Coordinates origin, Coordinates destination);

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

			Path* findPath(const Coordinates& start, const Coordinates& end);

		private:
			// void setPlayerUnits(int id, int unitnumbers[EUT_NUMBEROFUNITTYPES]);

			Board* board;
			int currentplayer;
			Player players[2];
			ENGINSTATES status;

			AbstractAlgorithm* pathfinder;
	};
}

#endif
