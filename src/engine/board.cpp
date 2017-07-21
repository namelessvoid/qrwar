#include <stdio.h>
#include <cassert>

#include "engine/board.hpp"
#include "engine/square.hpp"
#include "engine/pathfinding/astar.hpp"

namespace qrw
{
	Board::Board(int width, int height)
	:	_width(width),
	  _height(height)
	{
		// Initialize pathfinding
		_pathfinder = new AStar;
		_pathfinder->setBoard(this);
	}

	Board::~Board()
	{
		_units.clear();
		_terrains.clear();
		delete _pathfinder;
	}

	void Board::setUnit(const Coordinates &position, std::shared_ptr<Unit>& unit)
	{
		assert(!isUnitAt(position));
		_units[position] = unit;
	}

	void Board::removeUnit(const Coordinates &position)
	{
		assert(isUnitAt(position));
		_units.erase(position);
	}

	void Board::moveUnit(const Coordinates &source, const Coordinates &destination)
	{
		assert(isUnitAt(source));
		assert(!isUnitAt(destination));

		auto unit = _units.at(source);
		_units.erase(source);
		_units[destination] = unit;
	}

	bool Board::isUnitAt(const Coordinates &position)
	{
		return _units.find(position) != _units.end();
	}

	std::shared_ptr<Unit> Board::getUnit(const Coordinates &position)
	{
		auto iterator = _units.find(position);
		return iterator == _units.end() ? nullptr : iterator->second;
	}

	const std::map<Coordinates, std::shared_ptr<Unit> > &Board::getUnits() const
	{
		return _units;
	}

	void Board::setTerrain(const Coordinates &position, std::shared_ptr<Terrain> &terrain)
	{
		assert(!isTerrainAt(position));
		_terrains[position] = terrain;
	}

	void Board::removeTerrain(const Coordinates &position)
	{
		assert(isTerrainAt(position));
		_terrains.erase(position);
	}

	bool Board::isTerrainAt(const Coordinates &position)
	{
		return _terrains.find(position) != _terrains.end();
	}

	std::shared_ptr<Terrain> Board::getTerrain(const Coordinates &position)
	{
		auto iterator = _terrains.find(position);
		return iterator == _terrains.end() ? nullptr : iterator->second;
	}

	const std::map<Coordinates, std::shared_ptr<Terrain> > &Board::getTerrains() const
	{
		return _terrains;
	}

	int Board::getWidth()
	{
		return _width;
	}

	int Board::getHeight()
	{
		return _height;
	}

	bool Board::isOnBoard(Coordinates coordinates)
	{
		if(coordinates.getX() < 0 || coordinates.getX() >= _width)
			return false;
		if(coordinates.getY() < 0 || coordinates.getY() >= _height)
			return false;
		return true;
	}

	Path* Board::findPath(const Coordinates &start, const Coordinates &end)
	{
		return _pathfinder->findPath(start, end);
	}
}
