#include "engine/terrainfactory.hpp"

namespace qrw
{

Terrain*TerrainFactory::createTerrain(TERRAINTYPES terrainType)
{
	Terrain* terrain;

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

TerrainFactory::TerrainFactory()
{
}

} // namespace qrw

