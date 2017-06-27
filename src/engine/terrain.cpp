#include "engine/terrain.hpp"

namespace qrw
{

Terrain::Ptr Terrain::createTerrain(TERRAINTYPES terrainType)
{
	Terrain::Ptr terrain = nullptr;

	switch(terrainType)
	{
	case ET_WOOD:
		terrain = Terrain::Ptr(new Terrain(ET_WOOD, -1, 1));
		break;
	case ET_HILL:
		terrain = Terrain::Ptr(new Terrain(ET_HILL, 1, -1));
		break;
	default:
		terrain = Terrain::Ptr(new Terrain(ET_WALL, 1, 1));
		break;
	}

	return terrain;
}

Terrain::Terrain(TERRAINTYPES type, int attackmod, int defensemod)
	: _type(type),
	  _position(0, 0)
{
	_modificators[EM_ATTACK] = attackmod;
	_modificators[EM_DEFENSE] = defensemod;
}

Terrain::~Terrain()
{
}

int Terrain::getModificator(MODIFICATORS type)
{
	return _modificators[type];
}

int* Terrain::getModificators()
{
	return _modificators;
}

TERRAINTYPES Terrain::getType()
{
	return _type;
}

void Terrain::setPosition(const Coordinates& position)
{
	_position = position;
}

const Coordinates& Terrain::getPosition() const
{
	return _position;
}

} // namespace qrw
