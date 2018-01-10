#include <stdio.h>
#include <cassert>

#include "engine/board.hpp"
#include "engine/pathfinding/astar.hpp"

#include "foundation/spritecomponent.hpp"

#include "gui/texturemanager.hpp"

#include "game/renderlayers.hpp"

namespace qrw
{
	Board::Board(unsigned int width, unsigned int height)
	: _width(width),
	  _height(height)
	{
		// Initialize pathfinding
		_pathfinder = new pathfinding::AStar;
		_pathfinder->setBoard(this);

		SpriteComponent* backgroundComponent = new SpriteComponent(RENDER_LAYER_BACKGROUND);
		backgroundComponent->setTexture(TextureManager::getInstance()->getTexture("plainsquare"));
		backgroundComponent->setSize({32.0f * width, 32.0f * height});
		backgroundComponent->setRepeateTexture(true);
		addComponent(backgroundComponent);
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

	bool Board::isUnitAt(const Coordinates &position)
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

	bool Board::isTerrainAt(const Coordinates &position)
	{
		return _terrains.find(position) != _terrains.end();
	}

	Terrain* Board::getTerrain(const Coordinates &position)
	{
		auto iterator = _terrains.find(position);
		return iterator == _terrains.end() ? nullptr : iterator->second;
	}

	const std::map<Coordinates, Terrain*>& Board::getTerrains() const
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
		if(coordinates.getX() < 0 || static_cast<unsigned int>(coordinates.getX()) >= _width)
			return false;
		if(coordinates.getY() < 0 || static_cast<unsigned int>(coordinates.getY()) >= _height)
			return false;
		return true;
	}

	pathfinding::Path* Board::findPath(const Coordinates &start, const Coordinates &end)
	{
		return _pathfinder->findPath(start, end);
	}
}
