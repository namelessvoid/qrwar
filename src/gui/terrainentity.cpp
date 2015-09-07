#include "gui/terrainentity.hpp"

#include "gui/texturemanager.hpp"
#include "engine/coordinates.hpp"

namespace qrw
{

TerrainEntity::Ptr TerrainEntity::createTerrainEntity(Terrain::Ptr terrain, int dimension)
{
	return Ptr(new TerrainEntity(terrain, dimension));
}

TerrainEntity::TerrainEntity(Terrain::Ptr terrain, int dimension)
	: _terrain(terrain)
{
	setSize(sf::Vector2f(dimension, dimension));

	const Coordinates boardPosition = _terrain->getPosition();
	setPosition(sf::Vector2f(dimension * boardPosition.getX(), dimension * boardPosition.getY()));

	// Find correct texture
	const sf::Texture* texture = nullptr;

	switch(_terrain->getType())
	{
	case ET_WOOD:
		texture = TextureManager::getInstance()->getTexture("wood");
		break;
	case ET_HILL:
		texture = TextureManager::getInstance()->getTexture("hill");
		break;
	case ET_WALL:
		texture = TextureManager::getInstance()->getTexture("wall");
		break;
	default:
		texture = TextureManager::getInstance()->getFallbackTexture();
		break;
	}

	setTexture(texture);
}

} // namespace qrw

