#ifndef QRW_ASTAR_HPP
#define QRW_ASTAR_HPP

#include <set>
#include <map>

#include "engine/pathfinding/abstractalgorithm.hpp"
#include "engine/coordinates.hpp"

namespace qrw
{
	class Node;

	class AStar : public AbstractAlgorithm
	{
		public:
			AStar();
			~AStar();

			void setBoard(Board* board);
			Path* findPath(const Coordinates& start, const Coordinates& end);

		private:
			Coordinates* findLowestFCoordinates();
			void clear();

			Board* board;

			std::map<Coordinates*, Node*, Coordinates::PtrCompLess> nodemap;
			std::set<Coordinates*, Coordinates::PtrCompLess> openlist;
			std::set<Coordinates*, Coordinates::PtrCompLess> closedlist;

			Coordinates* directions[4];
	};
}
#endif
