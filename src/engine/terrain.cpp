#include "engine/terrain.hpp"

#include "gui/guihelper.hpp"
#include "gui/scene.hpp"

#include "foundation/spritecomponent.hpp"

#include "game/renderlayers.hpp"

namespace qrw
{

SID Terrain::typeName("qrw::Terrain");

Terrain* Terrain::createTerrain(TERRAINTYPES terrainType)
{
	const sf::Texture* texture = GuiHelper::getTerrainTexture(terrainType);

	int attackModifier = 0;
	int defenseModifier = 0;

	switch(terrainType)
	{
	case ET_WOOD:
		attackModifier = -1;
		defenseModifier = 1;
		break;
	case ET_HILL:
		attackModifier = 1;
		defenseModifier = -1;
		break;
	default:
		attackModifier = 1;
		defenseModifier = 1;
		break;
	}

	Terrain* terrain = g_scene.spawn<Terrain>();
	terrain->setTexture(texture);
	terrain->setModificator(EM_ATTACK, attackModifier);
	terrain->setModificator(EM_DEFENSE, defenseModifier);
	return terrain;
}

Terrain::Terrain()
	: _type(ET_NUMBEROFTERRAINTYPES),
	  _position(0, 0)
{
	_sprite = new SpriteComponent(RENDER_LAYER_TERRAIN);
	addComponent(_sprite);
	_sprite->setSize(sf::Vector2f(32, 32));

	_modificators[EM_ATTACK] = 0;
	_modificators[EM_DEFENSE] = 0;
}

Terrain::~Terrain()
{
	Board* board = g_scene.getSingleGameObject<Board>();
	if(board->getTerrain(_position) == this)
		board->removeTerrain(_position);
}

int Terrain::getModificator(MODIFICATORS type)
{
	return _modificators[type];
}

const int* Terrain::getModificators()
{
	return _modificators;
}

TERRAINTYPES Terrain::getType() const
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

void Terrain::setModificator(MODIFICATORS type, int value)
{
	assert(type >= 0);
	assert(type < EM_NUMMODIFICATORS);

	_modificators[type] = value;
}

void Terrain::setTexture(const sf::Texture* texture)
{
	_sprite->setTexture(texture);
}

} // namespace qrw
