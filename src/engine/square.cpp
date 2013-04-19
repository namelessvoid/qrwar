#include <cmath>

#include "engine/square.hpp"

namespace qrw
{
	Square::Square()
	:	terrain(0),
		unit(0),
		xpos(-1),
		ypos(-1)
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

	void Square::setPosition(int x, int y)
	{
		xpos = x;
		ypos = y;
	}

	int Square::getXPosition()
	{
		return xpos;
	}
	int Square::getYPosition()
	{
		return ypos;
	}

	int Square::getDistance(Square* square)
	{
		int dx = std::abs(xpos) - std::abs(square->getXPosition());
		int dy = std::abs(ypos) - std::abs(square->getYPosition());
		return ceilf(sqrt(dx * dx + dy * dy));
	}
}