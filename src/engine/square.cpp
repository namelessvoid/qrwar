#include <cmath>

#include "engine/square.hpp"

namespace qrw
{
	Square::Square(int x, int y)
	:	_terrain(0),
		_unit(0),
		_coordinates(x, y)
	{
		_terrain = 0;
		_unit = 0;
	}

	Square::~Square()
	{}

	void Square::setTerrain(Terrain::Ptr terrain)
	{
		this->_terrain = terrain;

		if(_terrain != nullptr)
			_terrain->setPosition(getCoordinates());
	}

	Terrain::Ptr Square::getTerrain()
	{
		return _terrain;
	}

	void Square::setUnit(Unit::Ptr unit)
	{
		this->_unit = unit;
	}

	Unit::Ptr Square::getUnit()
	{
		return _unit;
	}

	const Coordinates& Square::getCoordinates() const
	{
		return _coordinates;
	}

	int Square::getXPosition()
	{
		return _coordinates.getX();
	}
	int Square::getYPosition()
	{
		return _coordinates.getY();
	}

	int Square::getDistance(Square* square)
	{
		int dx = std::abs(getXPosition()) - std::abs(square->getXPosition());
		int dy = std::abs(getYPosition()) - std::abs(square->getYPosition());
		return ceilf(sqrt(dx * dx + dy * dy));
	}

	bool Square::isAccessible()
	{
		return getUnit() == 0;
	}
}
