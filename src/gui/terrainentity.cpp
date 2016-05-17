#include "gui/terrainentity.hpp"

#include "gui/guihelper.hpp"
#include "engine/coordinates.hpp"

namespace qrw
{

TerrainEntity::Ptr TerrainEntity::createTerrainEntity(Terrain::Ptr terrain, int dimension)
{
	return Ptr(new TerrainEntity(terrain, dimension));
}

const Coordinates& TerrainEntity::getBoardPosition() const
{
	return _terrain->getPosition();
}

TerrainEntity::TerrainEntity(Terrain::Ptr terrain, int dimension)
	: _terrain(terrain)
{
	setSize(sf::Vector2f(dimension, dimension));

	const Coordinates boardPosition = _terrain->getPosition();
	setPosition(sf::Vector2f(dimension * boardPosition.getX(), dimension * boardPosition.getY()));

    setTexture(GuiHelper::getTerrainTexture(terrain));
}

} // namespace qrw

