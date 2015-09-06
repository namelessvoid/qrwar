#ifndef QRW_TERRAINFACTORY_H
#define QRW_TERRAINFACTORY_H

#include "engine/terraintypes.hpp"
#include "engine/terrain.hpp"

namespace qrw
{

class TerrainFactory
{
public:
	static Terrain* createTerrain(TERRAINTYPES terrainType);

private:
	TerrainFactory();
};

} // namespace qrw

#endif // QRW_TERRAINFACTORY_H
