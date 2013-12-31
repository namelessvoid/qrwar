#include "engine/pathfinding/astar.hpp"

#include "engine/board.hpp"
#include "engine/unit.hpp"
#include "engine/pathfinding/path.hpp"

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
		// Check pre conditions
		if(board == 0)
			return 0;

		if(board->getSquare(start) == 0 || board->getSquare(end) == 0)
			return 0;

		if(board->getSquare(start)->getUnit() == 0)
			return 0;

		if(start == end)
			return 0;

		// Run the algorithm
		Unit* unit = board->getSquare(start)->getUnit();


		// Build the Path
		Path* path = new Path();

		// Cleanup and return.
		clear();
		return path;
	}

	void AStar::clear()
	{
		for(auto coordinate : openlist)
		{
			// Erase coordinate from closed list so it is not deleted twice.
			closedlist.erase(coordinate);
			delete coordinate;
		}
		openlist.clear();

		for(auto coordinate : closedlist)
		{
			delete coordinate;
		}
		closedlist.clear();
	}
}
