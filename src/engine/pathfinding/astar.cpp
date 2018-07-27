#include "engine/pathfinding/astar.hpp"

#include "engine/board.hpp"
#include "engine/unit.hpp"
#include "engine/pathfinding/path.hpp"
#include "engine/pathfinding/node.hpp"

namespace qrw
{
namespace pathfinding
{

AStar::AStar()
{
}

AStar::~AStar()
{
	clear();
}

Path* AStar::findPath(const qrw::Coordinates& start, const qrw::Coordinates& end)
{
	if(!worldAdapter_->isAccessible(end))
		return nullptr;

	if(start == end)
		return nullptr;

	// Clear everything that remained from previous steps
	clear();

	// Initialize the algorithm
	qrw::Coordinates currentcoords = start;
	Node<Coordinates>* currentnode = new Node<Coordinates>(currentcoords);
	Node<Coordinates>* tmpnode = 0;
	qrw::Coordinates neighbor;

	currentnode->setG(0);
	currentnode->setH(currentcoords.distanceTo(end));

	_nodemap[currentcoords] = currentnode;
	_openlist.insert(currentcoords);

	currentnode = nullptr;

	// Run the algorithm
	while(!_openlist.empty() && _closedlist.find(end) == _closedlist.end())
	{
		currentcoords = findLowestFCoordinates();
		_openlist.erase(currentcoords);
		currentnode = _nodemap[currentcoords];
		_closedlist.insert(currentcoords);

		// Check the neighbors
		for(auto neighbor : worldAdapter_->getNeighborLocationsFor(currentcoords))
		{
			// If the sqare is accessible but was not added to closedlist yet
			if(_closedlist.find(neighbor) == _closedlist.end()
				&& worldAdapter_->isAccessible(neighbor))
			{
				// Coordinates are not put into openlist
				if(_openlist.find(neighbor) == _openlist.end())
				{
					tmpnode = new Node(neighbor);
					tmpnode->setG(currentnode->getG() + 1);
					tmpnode->setH(neighbor.distanceTo(end));
					tmpnode->setParent(currentnode);

					_nodemap[neighbor] = tmpnode;
					_openlist.insert(neighbor);
				}
				else
				{
					tmpnode = _nodemap[neighbor];

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
	if(_closedlist.find(end) == _closedlist.end())
		return nullptr;

	Path* path = new Path();

	for(currentnode = _nodemap[end];
		currentnode->getParent() != 0;
		currentnode = currentnode->getParent())
	{
		path->prependStep(currentnode->getLocation());
	}
	path->prependStep(start);

	return path;
}

qrw::Coordinates AStar::findLowestFCoordinates()
{
	if(_openlist.size() == 0)
		return Coordinates(0, 0);
	else if(_openlist.size() == 1)
		return *_openlist.begin();

	qrw::Coordinates lowestcoordinate = *_openlist.begin();
	Node<Coordinates>* lowestfnode = _nodemap[lowestcoordinate];
	Node<Coordinates>* currentnode =  0;

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
	}

	_openlist.clear();
	_closedlist.clear();
}

} // namespace pathfinding
} // namespace qrw
