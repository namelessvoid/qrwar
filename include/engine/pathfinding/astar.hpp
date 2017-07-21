#ifndef QRW_ASTAR_HPP
#define QRW_ASTAR_HPP

#include <set>
#include <map>

#include "engine/pathfinding/abstractpathfinder.hpp"
#include "engine/coordinates.hpp"

namespace qrw
{
	class Node;

	class AStar : public AbstractPathfinder
	{
		public:
			AStar();
			~AStar();

			void setBoard(Board* _board);
			Path* findPath(const Coordinates& start, const Coordinates& end);

		private:
			Coordinates findLowestFCoordinates();

			void clear();

			Board* _board;

			std::map<Coordinates, Node*> _nodemap;
			std::set<Coordinates> _openlist;
			std::set<Coordinates> _closedlist;

			Coordinates* _directions[4];
	};
}
#endif
