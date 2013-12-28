#include "engine/pathfinding/astar.hpp"

namespace qrw
{
	AStar::~AStar()
	{
		clear();
	}

	void AStar::setBoard(Board* board)
	{
		this->board = board;
	}

	Path* AStar::getPath(const Coordinates& start, const Coordinates& end)
	{
		return 0;
	}

	void AStar::clear()
	{
		for(auto coordinate : openlist)
			openlist.clear();

		for(auto coordinate : closedlist)
			delete coordinate;
		closedlist.clear();
	}
}
