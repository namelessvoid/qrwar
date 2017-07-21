#include "engine/pathfinding/astar.hpp"

#include <cmath>

#include "engine/board.hpp"
#include "engine/square.hpp"
#include "engine/unit.hpp"
#include "engine/pathfinding/path.hpp"
#include "engine/pathfinding/node.hpp"

namespace qrw
{
	AStar::AStar()
	{
		_directions[0] = new Coordinates(-1,  0);
		_directions[1] = new Coordinates( 0, -1);
		_directions[2] = new Coordinates(+1,  0);
		_directions[3] = new Coordinates( 0, +1);
	}

	AStar::~AStar()
	{
		clear();

		for(int i = 0; i < 4; ++i)
			 delete _directions[i];
	}

	void AStar::setBoard(Board* board)
	{
		this->_board = board;
	}

	Path* AStar::findPath(const Coordinates& start, const Coordinates& end)
	{
		// Check pre conditions
		if(_board == nullptr)
			return nullptr;

		if(!_board->isOnBoard(start) || !_board->isOnBoard(end))
			return nullptr;

		if(start == end)
			return nullptr;

		// Clear everything that remained from previous steps
		clear();

		// Initialize the algorithm
		Coordinates* currentcoords = new Coordinates(start);
		Node* currentnode = new Node(*currentcoords);
		Node* tmpnode = 0;
		Coordinates* tmpcoords = 0;

		currentnode->setG(0);
		currentnode->setH(getDistance(*currentcoords, end));

		_nodemap[currentcoords] = currentnode;
		_openlist.insert(currentcoords);

		currentcoords = currentnode = 0;
		Coordinates* endcoords = new Coordinates(end);

		// Run the algorithm
		while(!_openlist.empty() && _closedlist.find(endcoords) == _closedlist.end())
		{
			currentcoords = findLowestFCoordinates();
			_openlist.erase(currentcoords);
			currentnode = _nodemap[currentcoords];
			_closedlist.insert(currentcoords);

			// Check the neighbours
			for(auto direction : _directions)
			{
				tmpcoords = new Coordinates(*currentcoords + *direction);

				// If the sqare is accessible but was not added to closedlist yet
				if(_closedlist.find(tmpcoords) == _closedlist.end()
					&& _board->isOnBoard(*tmpcoords)
					&& !_board->isUnitAt(*tmpcoords))
				{
					// Coordinates are not put into openlist
					if(_openlist.find(tmpcoords) == _openlist.end())
					{
						tmpnode = new Node(*tmpcoords);
						tmpnode->setG(currentnode->getG() + 1);
						tmpnode->setH(getDistance(*tmpcoords, end));
						tmpnode->setParent(currentnode);

						_nodemap[tmpcoords] = tmpnode;
						_openlist.insert(tmpcoords);
					}
					else
					{
						tmpnode = _nodemap[tmpcoords];
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
		if(_closedlist.find(endcoords) == _closedlist.end())
			return nullptr;

		Path* path = new Path();

		for(currentnode = _nodemap[endcoords];
			currentnode->getParent() != 0;
			currentnode = currentnode->getParent())
		{
			path->prependStep(*currentnode);
		}
		path->prependStep(start);

		// Cleanup and return.
		delete endcoords;

		return path;
	}

	Coordinates* AStar::findLowestFCoordinates()
	{
		if(_openlist.size() == 0)
			return 0;
		else if(_openlist.size() == 1)
			return *_openlist.begin();

		Coordinates* lowestcoordinate = *_openlist.begin();
		Node* lowestfnode = _nodemap[lowestcoordinate];
		Node * currentnode =  0;

		for(auto coordinate : _openlist)
		{
			currentnode = _nodemap[coordinate];
			if(currentnode->getF() < lowestfnode->getF())
			{
				lowestcoordinate = coordinate;
				lowestfnode = currentnode;
			}
		}

		return lowestcoordinate;
	}

	int AStar::getDistance(const Coordinates &a, const Coordinates &b)
	{
		int dx = std::abs(a.getX()) - std::abs(b.getX());
		int dy = std::abs(a.getY()) - std::abs(b.getY());
		return ceilf(sqrt(dx * dx + dy * dy));
	}


	void AStar::clear()
	{
		for(auto nodemapiter : _nodemap)
		{
			delete nodemapiter.second;
		}
		_nodemap.clear();

		for(auto coordinate : _openlist)
		{
			// Erase coordinate from closed list so it is not deleted twice.
			_closedlist.erase(coordinate);
			delete coordinate;
		}
		_openlist.clear();

		for(auto coordinate : _closedlist)
		{
			delete coordinate;
		}
		_closedlist.clear();
	}
}
