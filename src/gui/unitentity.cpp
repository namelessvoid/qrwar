#include "gui/unitentity.hpp"

#include "engine/unit.hpp"
#include "engine/coordinates.hpp"
#include "engine/player.hpp"

#include "gui/texturemanager.hpp"

namespace qrw {

UnitEntity::Ptr UnitEntity::createUnitEntity(Unit::Ptr unit, int dimension)
{
	return Ptr(new UnitEntity(unit, dimension));
}

UnitEntity::UnitEntity(Unit::Ptr unit, int dimension)
	: _unit(unit)
{
	setSize(sf::Vector2f(dimension, dimension));

	const Coordinates boardPosition = _unit->getPosition();
	setPosition(sf::Vector2f(dimension * boardPosition.getX(), dimension * boardPosition.getY()));

	// Find correct texture
	std::string textureName = "p" + std::to_string(_unit->getPlayer()->getId());

	switch(_unit->getType())
	{
	case EUT_SWORDMAN:
		textureName += "swordman";
		break;
	case EUT_ARCHER:
		textureName += "archer";
		break;
	case EUT_SPEARMAN:
		textureName += "spearman";
		break;
	default:
		textureName = "";
	}

	TextureManager* textureManager = TextureManager::getInstance();
	const sf::Texture* texture = textureName != "" ? textureManager->getTexture(textureName) : textureManager->getFallbackTexture();
	setTexture(texture);
}

} // namespace qrw
