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
	template<class TSpatialRepresentation>
	class Node;
	class Path;

class AStar : public AbstractPathfinder<Coordinates>
	{
		public:
			AStar();
			~AStar() override;

			Path* findPath(const qrw::Coordinates& start, const qrw::Coordinates& end) override;

		private:
			qrw::Coordinates findLowestFCoordinates();

			void clear();

			std::map<Coordinates, Node<Coordinates>*> _nodemap;
			std::set<Coordinates> _openlist;
			std::set<Coordinates> _closedlist;
	};
} // namespace pathfinding
} // namespace qrw

#endif // QRW_PATHFINDING_ASTAR_HPP
