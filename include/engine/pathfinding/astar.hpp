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
			~AStar();

			void setBoard(Board* board);
			Path* getPath(const Coordinates& start, const Coordinates& end);

		private:
			void clear();

			Board* board;

			std::map<Coordinates*, Node*> nodemap;
			std::set<Coordinates*, Coordinates::PtrCompLess> openlist;
			std::set<Coordinates*, Coordinates::PtrCompLess> closedlist;
	};
}
#endif
