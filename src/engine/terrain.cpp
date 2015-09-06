#include "engine/terrain.hpp"

namespace qrw
{

Terrain* Terrain::createTerrain(TERRAINTYPES terrainType)
{
	Terrain* terrain = nullptr;

	switch(terrainType)
	{
	case ET_WOOD:
		terrain = new Terrain(ET_WOOD, -1, 1);
		break;
	case ET_HILL:
		terrain = new Terrain(ET_HILL, 1, -1);
		break;
	default:
		terrain = new Terrain(ET_WALL, 1, 1);
		break;
	}

	return terrain;
}

Terrain::Terrain(TERRAINTYPES type, int attackmod, int defensemod)
: _type(type)
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

} // namespace qrw
