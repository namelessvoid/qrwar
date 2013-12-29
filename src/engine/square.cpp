#include <cmath>

#include "engine/square.hpp"

namespace qrw
{
	Square::Square(int x, int y)
	:	terrain(0),
		unit(0),
		coordinates(x, y)
	{
		terrain = 0;
		unit = 0;
	}

	Square::~Square()
	{}

	void Square::setTerrain(Terrain* terrain)
	{
		this->terrain = terrain;
	}
	Terrain* Square::getTerrain()
	{
		return terrain;
	}

	void Square::setUnit(Unit* unit)
	{
		this->unit = unit;
	}
	Unit* Square::getUnit()
	{
		return unit;
	}

	const Coordinates& Square::getCoordinates() const
	{
		return coordinates;
	}

	int Square::getXPosition()
	{
		return coordinates.getX();
	}
	int Square::getYPosition()
	{
		return coordinates.getY();
	}

	int Square::getDistance(Square* square)
	{
		int dx = std::abs(getXPosition()) - std::abs(square->getXPosition());
		int dy = std::abs(getYPosition()) - std::abs(square->getYPosition());
		return ceilf(sqrt(dx * dx + dy * dy));
	}
}