#include "engine/square.hpp"

namespace qrw
{
	Square::Square()
	:	terrain(0),
		unit(0)
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
}