#include "engine/terrain.hpp"

#include "gui/guihelper.hpp"

#include "foundation/spritecomponent.hpp"

#include "game/renderlayers.hpp"

namespace qrw
{

Terrain* Terrain::createTerrain(TERRAINTYPES terrainType)
{
	Terrain* terrain = nullptr;
	const sf::Texture* texture = GuiHelper::getTerrainTexture(terrainType);

	switch(terrainType)
	{
	case ET_WOOD:
		terrain = new Terrain(ET_WOOD, -1, 1, texture);
		break;
	case ET_HILL:
		terrain = new Terrain(ET_HILL, 1, -1, texture);
		break;
	default:
		terrain = new Terrain(ET_WALL, 1, 1, texture);
		break;
	}

	return terrain;
}

Terrain::Terrain(TERRAINTYPES type, int attackmod, int defensemod, const sf::Texture* texture)
	: _type(type),
	  _position(0, 0)
{
	_sprite = new SpriteComponent(RENDER_LAYER_TERRAIN);
	addComponent(_sprite);
	_sprite->setSize(sf::Vector2f(32, 32));
	_sprite->setTexture(texture);

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
	_sprite->setPosition(sf::Vector2f(32 * _position.getX(), 32 * _position.getY()));
}

const Coordinates& Terrain::getPosition() const
{
	return _position;
}

} // namespace qrw
