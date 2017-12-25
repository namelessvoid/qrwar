#ifndef QRW_PATHFINDING_ASTAR_HPP
#define QRW_PATHFINDING_ASTAR_HPP

#include <set>
#include <map>

#include "engine/pathfinding/abstractpathfinder.hpp"
#include "engine/coordinates.hpp"

namespace qrw
{
namespace pathfinding
{
	class Node;
	class Path;

	class AStar : public AbstractPathfinder
	{
		public:
			AStar();
			~AStar();

			void setBoard(Board* _board);
			Path* findPath(const qrw::Coordinates& start, const qrw::Coordinates& end);

		private:
			qrw::Coordinates findLowestFCoordinates();

			void clear();

			Board* _board;

			std::map<Coordinates, Node*> _nodemap;
			std::set<Coordinates> _openlist;
			std::set<Coordinates> _closedlist;

			Coordinates* _directions[4];
	};
} // namespace pathfinding
} // namespace qrw

#endif // QRW_PATHFINDING_ASTAR_HPP
