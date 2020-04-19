#include "game/skirmish/ladder.hpp"

#include "foundation/spritecomponent.hpp"

#include "gui/texturemanager.hpp"

#include "game/constants.hpp"
#include "game/renderlayers.hpp"
#include "game/skirmish/boardtoworldconversion.hpp"
#include "game/skirmish/isometricconversion.hpp"

namespace qrw
{

Ladder::Ladder()
{
	spriteComponent_ = new SpriteComponent(RENDER_LAYER_GAME);
	spriteComponent_->setSize({2.0f * SQUARE_DIMENSION, SQUARE_DIMENSION});
	spriteComponent_->setOrigin(SQUARE_DIMENSION, 0);
	addComponent(spriteComponent_);
}

const SID& Ladder::getTypeName() const
{
	throw "Not implemented";
}

const sf::Texture* Ladder::getTexture() const
{
	return spriteComponent_->getTexture();
}

void Ladder::setFace(const Coordinates& face)
{
	const sf::Texture* texture = TextureManager::getInstance()->getFallbackTexture();
	sf::Vector2f origin;

	WallAccessStructureBase::setFace(face);
	if(getFace() == Directions::NORTH) {
		texture = TextureManager::getInstance()->getTexture("ladder_north");
		origin = sf::Vector2f(10, 69);
	} else if(getFace() == Directions::EAST) {
		texture = TextureManager::getInstance()->getTexture("ladder_east");
		origin = sf::Vector2f(12, 42);
	} else if(getFace() == Directions::SOUTH) {
		texture = TextureManager::getInstance()->getTexture("ladder_south");
		origin = sf::Vector2f(34, 42);
	} else if(getFace() == Directions::WEST) {
		texture = TextureManager::getInstance()->getTexture("ladder_west");
		origin = sf::Vector2f(34, 69);
	}

	spriteComponent_->setSize(sf::Vector2f(texture->getSize()));
	spriteComponent_->setOrigin(origin.x, origin.y);
	spriteComponent_->setTexture(texture);
}

void Ladder::setPosition(const Coordinates& position)
{
	Structure::setPosition(position);
	spriteComponent_->setPosition(worldToIso(boardToWorld(position)));
}

} // namespace qrw