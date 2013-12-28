#ifndef QRW_ASTAR_HPP
#define QRW_ASTAR_HPP

#include <set>

#include "engine/pathfinding/abstractalgorithm.hpp"
#include "engine/coordinates.hpp"

namespace qrw
{
	class AStar : public AbstractAlgorithm
	{
		public:
			void setBoard(Board* board);
			Path* getPath(const Coordinates& start, const Coordinates& end);

		private:
			Board* board;

			std::set<Coordinates*, Coordinates::PtrCompLess> openlist;
			std::set<Coordinates*, Coordinates::PtrCompLess> closedlist;
	};
}
#endif
