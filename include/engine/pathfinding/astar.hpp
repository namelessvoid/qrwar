#ifndef QRW_PATHFINDING_ASTAR_HPP
#define QRW_PATHFINDING_ASTAR_HPP

#include <set>
#include <map>

#include "engine/pathfinding/abstractpathfinder.hpp"
#include "engine/pathfinding/path.hpp"
#include "engine/pathfinding/node.hpp"

#include "game/skirmish/coordinates.hpp"

namespace qrw
{
namespace pathfinding
{

template<typename TSpatialRepresentation>
class AStar : public AbstractPathfinder<TSpatialRepresentation>
{
public:
	AStar() = default;
	~AStar() override { clear(); }

	Path* findPath(const TSpatialRepresentation& start, const TSpatialRepresentation& end) override;

private:
	TSpatialRepresentation findLowestF();

	void clear();

	std::map<TSpatialRepresentation, Node<TSpatialRepresentation>*> _nodemap;
	std::set<Coordinates> _openlist;
	std::set<Coordinates> _closedlist;
};

template<class TSpatialRepresentation>
Path* AStar<TSpatialRepresentation>::findPath(const TSpatialRepresentation& start, const TSpatialRepresentation& end)
{
	if(start == end)
		return nullptr;

	// Clear everything that remained from previous steps
	clear();

	// Initialize the algorithm
	TSpatialRepresentation currentcoords = start;
	auto currentnode = new Node<TSpatialRepresentation>(currentcoords);
	Node<TSpatialRepresentation>* tmpnode = 0;

	currentnode->setG(0);
	currentnode->setH(currentcoords.distanceTo(end));

	_nodemap[currentcoords] = currentnode;
	_openlist.insert(currentcoords);

	currentnode = nullptr;

	// Run the algorithm
	while(!_openlist.empty() && _closedlist.find(end) == _closedlist.end())
	{
		currentcoords = findLowestF();
		_openlist.erase(currentcoords);
		currentnode = _nodemap[currentcoords];
		_closedlist.insert(currentcoords);

		// Check the neighbors
		for(const auto& neighbor : this->worldAdapter_->getNeighborLocationsFor(currentcoords))
		{
			// If the sqare is accessible but was not added to closedlist yet
			if(_closedlist.find(neighbor) == _closedlist.end()
			   && this->worldAdapter_->isAccessibleFrom(currentcoords, neighbor))
			{
				// Coordinates are not put into openlist
				if(_openlist.find(neighbor) == _openlist.end())
				{
					tmpnode = new Node<qrw::Coordinates>(neighbor);
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

	auto path = new Path();

	for(currentnode = _nodemap[end];
		currentnode->getParent() != 0;
		currentnode = currentnode->getParent())
	{
		path->prependStep(currentnode->getLocation());
	}
	path->prependStep(start);

	return path;
}

template<class TSpatialRepresentation>
TSpatialRepresentation AStar<TSpatialRepresentation>::findLowestF()
{
	if(_openlist.size() == 0)
		return Coordinates(0, 0);
	else if(_openlist.size() == 1)
		return *_openlist.begin();

	TSpatialRepresentation lowestcoordinate = *_openlist.begin();
	Node<TSpatialRepresentation>* lowestfnode = _nodemap[lowestcoordinate];
	Node<TSpatialRepresentation>* currentnode =  0;

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

template<class TSpatialRepresentation>
void AStar<TSpatialRepresentation>::clear()
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

#endif // QRW_PATHFINDING_ASTAR_HPP
