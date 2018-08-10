#include "engine/terrain.hpp"

#include "gui/guihelper.hpp"
#include "gui/scene.hpp"

#include "foundation/spritecomponent.hpp"

#include "game/renderlayers.hpp"
#include "game/constants.hpp"

namespace qrw
{

SID Terrain::typeName("qrw::Terrain");

Terrain* Terrain::createTerrain(TERRAINTYPES terrainType)
{
	int attackModifier = 0;
	int defenseModifier = 0;

	switch(terrainType)
	{
	case TERRAINTYPES::ET_WOOD:
		attackModifier = -1;
		defenseModifier = 1;
		break;
	case TERRAINTYPES::ET_HILL:
		attackModifier = 1;
		defenseModifier = -1;
		break;
	default:
		attackModifier = 1;
		defenseModifier = 1;
		break;
	}

	Terrain* terrain = new Terrain();
	terrain->_modificators[EM_ATTACK] = attackModifier;
	terrain->_modificators[EM_DEFENSE] = defenseModifier;
	terrain->_type = terrainType;
	return terrain;
}

Terrain::Terrain()
	: _type(TERRAINTYPES::ET_NUMBEROFTERRAINTYPES),
	  _position(0, 0)
{
	_sprite = new SpriteComponent(RENDER_LAYER_TERRAIN);
	addComponent(_sprite);
	_sprite->setSize(sf::Vector2f(SQUARE_DIMENSION, SQUARE_DIMENSION));

	_modificators[EM_ATTACK] = 0;
	_modificators[EM_DEFENSE] = 0;
}

Terrain::~Terrain()
{
}

int Terrain::getModificator(MODIFICATORS type) const
{
	return _modificators[type];
}

TERRAINTYPES Terrain::getType() const
{
	return _type;
}

void Terrain::setPosition(const Coordinates& position)
{
	_position = position;
	_sprite->setPosition(sf::Vector2f(SQUARE_DIMENSION * _position.getX(), SQUARE_DIMENSION * _position.getY()));
}

const Coordinates& Terrain::getPosition() const
{
	return _position;
}

void Terrain::onAddToScene()
{
	GameObject::onAddToScene();
	const sf::Texture* texture = GuiHelper::getTerrainTexture(_type);
	_sprite->setTexture(texture);
}

} // namespace qrw
