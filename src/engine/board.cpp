#include <stdio.h>
#include <cassert>

#include "engine/board.hpp"
#include "engine/pathfinding/astar.hpp"

#include "foundation/spritecomponent.hpp"

#include "gui/texturemanager.hpp"

#include "game/renderlayers.hpp"
#include "game/constants.hpp"

namespace qrw
{

SID Board::typeName("qrw::Board");

	Board::Board(unsigned int width, unsigned int height)
	: _width(width),
	  _height(height)
	{
		// Initialize pathfinding
		_pathfinder = new pathfinding::AStar;
		_pathfinder->setBoard(this);

		backgroundComponent_ = new SpriteComponent(RENDER_LAYER_BACKGROUND);
		backgroundComponent_->setTexture(TextureManager::getInstance()->getTexture("plainsquare"));
		addComponent(backgroundComponent_);

		resizeBackground();
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

	bool Board::isOnBoard(Coordinates coordinates)
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
		resizeBackground();

	}

	void Board::setHeight(unsigned int height)
	{
		_height = height;
		resizeBackground();
	}

	pathfinding::Path* Board::findPath(const Coordinates &start, const Coordinates &end)
	{
		return _pathfinder->findPath(start, end);
	}

	void Board::resizeBackground()
	{
		backgroundComponent_->setSize({SQUARE_DIMENSION * _width, SQUARE_DIMENSION * _height});
		backgroundComponent_->setRepeateTexture(true, 2.0f);
	}
}
