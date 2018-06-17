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
	_directions[0] = new qrw::Coordinates(-1,  0);
	_directions[1] = new qrw::Coordinates( 0, -1);
	_directions[2] = new qrw::Coordinates(+1,  0);
	_directions[3] = new qrw::Coordinates( 0, +1);
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

Path* AStar::findPath(const qrw::Coordinates& start, const qrw::Coordinates& end)
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
	qrw::Coordinates currentcoords = start;
	Node* currentnode = new Node(currentcoords);
	Node* tmpnode = 0;
	qrw::Coordinates tmpcoords;

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

		// Check the neighbours
		for(auto direction : _directions)
		{
			tmpcoords = currentcoords + *direction;

			// If the sqare is accessible but was not added to closedlist yet
			if(_closedlist.find(tmpcoords) == _closedlist.end()
				&& _board->isOnBoard(tmpcoords)
				&& !_board->isUnitAt(tmpcoords))
			{
				// Coordinates are not put into openlist
				if(_openlist.find(tmpcoords) == _openlist.end())
				{
					tmpnode = new Node(tmpcoords);
					tmpnode->setG(currentnode->getG() + 1);
					tmpnode->setH(tmpcoords.distanceTo(end));
					tmpnode->setParent(currentnode);

					_nodemap[tmpcoords] = tmpnode;
					_openlist.insert(tmpcoords);
				}
				else
				{
					tmpnode = _nodemap[tmpcoords];

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
		path->prependStep(*currentnode);
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
