#include "engine/pathfinding/astar.hpp"

namespace qrw
{
	void AStar::setBoard(Board* board)
	{
		this->board = board;
	}

	Path* AStar::getPath(const Coordinates& start, const Coordinates& end)
	{
		return 0;
	}
}
