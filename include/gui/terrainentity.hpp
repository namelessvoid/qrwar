#ifndef QRW_TERRAINENTITY_H
#define QRW_TERRAINENTITY_H

#include <SFML/Graphics/RectangleShape.hpp>

#include "engine/terrain.hpp"

namespace qrw
{

class TerrainEntity : public sf::RectangleShape
{
public:
	typedef std::shared_ptr<TerrainEntity> Ptr;

	static Ptr createTerrainEntity(Terrain::Ptr terrain, int dimension);

private:
	TerrainEntity(Terrain::Ptr terrain, int dimension);

	Terrain::Ptr _terrain;
};

} // namespace qrw

#endif // QRW_TERRAINENTITY_H
