#include "engine/pathfinding/astar.hpp"

#include "engine/board.hpp"
#include "engine/unit.hpp"
#include "engine/pathfinding/path.hpp"
#include "engine/pathfinding/node.hpp"

namespace qrw
{
	AStar::AStar()
	{
		directions[0] = new Coordinates(-1,  0);
		directions[1] = new Coordinates( 0, -1);
		directions[2] = new Coordinates(+1,  0);
		directions[3] = new Coordinates( 0, +1);
	}

	AStar::~AStar()
	{
		clear();

		for(int i = 0; i < 4; ++i)
			 delete directions[i];
	}

	void AStar::setBoard(Board* board)
	{
		this->board = board;
	}

	Path* AStar::findPath(const Coordinates& start, const Coordinates& end)
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

		// Initialize the algorithm
		Coordinates* currentcoords = new Coordinates(start);
		Node* currentnode = new Node(*currentcoords);
		Node* tmpnode = 0;
		Coordinates* tmpcoords = 0;

		currentnode->setG(0);
		currentnode->setH(board->getSquare(*currentcoords)->getDistance(board->getSquare(end)));

		nodemap[currentcoords] = currentnode;
		openlist.insert(currentcoords);

		currentcoords = currentnode = 0;
		Coordinates* endcoords = new Coordinates(end);

		// Run the algorithm
		while(!openlist.empty() && closedlist.find(endcoords) == closedlist.end())
		{
			currentcoords = findLowestFCoordinates();
			openlist.erase(currentcoords);
			currentnode = nodemap[currentcoords];
			closedlist.insert(currentcoords);

			// Check the neighbours
			for(auto direction : directions)
			{
				tmpcoords = new Coordinates(*currentcoords + *direction);

				// If the sqare is accessible but was not added to closedlist yet
				if(closedlist.find(tmpcoords) == closedlist.end()
					&& board->getSquare(*tmpcoords) != 0
					&& board->getSquare(*tmpcoords)->isAccessible())
				{
					// Coordinates are not put into openlist
					if(openlist.find(tmpcoords) == openlist.end())
					{
						tmpnode = new Node(*tmpcoords);
						tmpnode->setG(currentnode->getG() + 1);
						tmpnode->setH(board->getSquare(*tmpcoords)->getDistance(board->getSquare(end)));
						tmpnode->setParent(currentnode);

						nodemap[tmpcoords] = tmpnode;
						openlist.insert(tmpcoords);
					}
					else
					{
						tmpnode = nodemap[tmpcoords];
						delete tmpcoords;
						tmpcoords = 0;

						if(currentnode->getG() + 1 < tmpnode->getG())
						{
							tmpnode->setParent(currentnode);
							tmpnode->setG(currentnode->getG() + 1);
						}
					}
				} // if(accessible && not on closedlist)
			} // for(directions)
		} // for(openlist not empty && end not reached)

		// Build the Path
		if(closedlist.find(endcoords) == closedlist.end())
			return 0;

		Path* path = new Path();

		for(currentnode = nodemap[endcoords];
			currentnode->getParent() != 0;
			currentnode = currentnode->getParent())
		{
			path->prependStep(board->getSquare(*currentnode));
		}
		path->prependStep(board->getSquare(start));

		// Cleanup and return.
		clear();
		delete endcoords;

		return path;
	}

	Coordinates* AStar::findLowestFCoordinates()
	{
		if(openlist.size() == 0)
			return 0;
		else if(openlist.size() == 1)
			return *openlist.begin();

		Coordinates* lowestcoordinate = *openlist.begin();
		Node* lowestfnode = nodemap[lowestcoordinate];
		Node * currentnode =  0;

		for(auto coordinate : openlist)
		{
			currentnode = nodemap[coordinate];
			if(currentnode->getF() < lowestfnode->getF())
			{
				lowestcoordinate = coordinate;
				lowestfnode = currentnode;
			}
		}

		return lowestcoordinate;
	}


	void AStar::clear()
	{
		for(auto nodemapiter : nodemap)
		{
			delete nodemapiter.second;
		}
		nodemap.clear();

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
