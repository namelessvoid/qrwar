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

			void setBoard(Board* _board);
			Path* findPath(const Coordinates& start, const Coordinates& end);

		private:
			Coordinates* findLowestFCoordinates();
			void clear();

			Board* _board;

			std::map<Coordinates*, Node*, Coordinates::PtrCompLess> _nodemap;
			std::set<Coordinates*, Coordinates::PtrCompLess> _openlist;
			std::set<Coordinates*, Coordinates::PtrCompLess> _closedlist;

			Coordinates* _directions[4];
	};
}
#endif
