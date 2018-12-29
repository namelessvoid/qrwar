#include <stdio.h>
#include <cassert>

#include "engine/board.hpp"
#include "engine/pathfinding/astar.hpp"

#include "foundation/spritecomponent.hpp"

#include "gui/texturemanager.hpp"

#include "game/renderlayers.hpp"
#include "game/constants.hpp"

#include "game/skirmish/boardbackgroundcomponent.hpp"

namespace qrw
{

SID Board::typeName("qrw::Board");

	Board::Board(unsigned int width, unsigned int height)
	: _width(width),
	  _height(height),
	  pathfindingAdapter_(*this)
	{
		// Initialize pathfinding
		_pathfinder = new pathfinding::AStar<Coordinates>;
		_pathfinder->setWorldAdapter(pathfindingAdapter_);

		backgroundComponent_ = new BoardBackgroundComponent(*this);
		addComponent(backgroundComponent_);
	}

	Board::~Board()
	{
		_units.clear();
		_terrains.clear();
		delete _pathfinder;
	}

	void Board::setUnit(const Coordinates &position, Unit* unit)
	{
		assert(!isUnitAt(position));
		_units[position] = unit;
	}

	void Board::removeUnit(const Coordinates &position)
	{
		assert(isUnitAt(position));
		_units.erase(position);
	}

	bool Board::isUnitAt(const Coordinates &position) const
	{
		return _units.find(position) != _units.end();
	}

	Unit* Board::getUnit(const Coordinates &position)
	{
		auto iterator = _units.find(position);
		return iterator == _units.end() ? nullptr : iterator->second;
	}

	const std::map<Coordinates, Unit*> &Board::getUnits() const
	{
		return _units;
	}

	void Board::setTerrain(const Coordinates &position, Terrain* terrain)
	{
		assert(!isTerrainAt(position));
		_terrains[position] = terrain;
	}

	void Board::removeTerrain(const Coordinates &position)
	{
		assert(isTerrainAt(position));
		_terrains.erase(position);
	}

	bool Board::isTerrainAt(const Coordinates &position) const
	{
		return _terrains.find(position) != _terrains.end();
	}

	Terrain* Board::getTerrain(const Coordinates &position)
	{
		auto iterator = _terrains.find(position);
		return iterator == _terrains.end() ? nullptr : iterator->second;
	}

	std::map<Coordinates, Terrain*>& Board::getTerrains()
	{
		return _terrains;
	}

void Board::setStructure(const Coordinates& position, Structure* structure)
{
	assert(!isStructureAt(position));
	structures_[position] = structure;
}

Structure* Board::getStructure(const Coordinates& position) const
{
	auto iterator = structures_.find(position);
	return iterator == structures_.end() ? nullptr : iterator->second;
}

bool Board::isStructureAt(const Coordinates& position) const
{
	return structures_.find(position) != structures_.end();
}

void Board::removeStructureAt(const Coordinates& position)
{
	assert(isStructureAt(position));
	structures_.erase(position);
}

std::map<Coordinates, Structure*> Board::getStructures()
{
	return structures_;
}

	bool Board::isOnBoard(Coordinates coordinates) const
	{
		if(coordinates.getX() < 0 || static_cast<unsigned int>(coordinates.getX()) >= _width)
			return false;
		if(coordinates.getY() < 0 || static_cast<unsigned int>(coordinates.getY()) >= _height)
			return false;
		return true;
	}

	void Board::setWidth(unsigned int width)
	{
		_width = width;
	}

	void Board::setHeight(unsigned int height)
	{
		_height = height;
	}

	pathfinding::Path* Board::findPath(const Coordinates &start, const Coordinates &end)
	{
		return _pathfinder->findPath(start, end);
	}
}
