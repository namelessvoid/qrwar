#include "game/skirmish/stairs.hpp"

#include "game/skirmish/isometricconversion.hpp"
#include "game/skirmish/boardtoworldconversion.hpp"
#include "gui/texturemanager.hpp"
#include "foundation/spritecomponent.hpp"
#include "game/constants.hpp"
#include "game/renderlayers.hpp"

namespace qrw
{

SID Stairs::typeName("qrw::Stairs");

Stairs::Stairs()
{
	spriteComponent_ = new SpriteComponent(RENDER_LAYER_GAME);
	spriteComponent_->setSize({2.0f * SQUARE_DIMENSION, 91.0f});
	//spriteComponent_->setScale({2.0f, 2.0f});
	spriteComponent_->setOrigin(SQUARE_DIMENSION, 40.0f);
	spriteComponent_->setTexture(TextureManager::getInstance()->getTexture("stairs_west"));
	addComponent(spriteComponent_);
}

const sf::Texture* Stairs::getTexture() const
{
	return spriteComponent_->getTexture();
}

void Stairs::setPosition(const Coordinates& position)
{
	Structure::setPosition(position);

	sf::Vector2f isometricPosition = worldToIso({SQUARE_DIMENSION * position_.getX(), SQUARE_DIMENSION * position.getY()});
	spriteComponent_->setPosition(isometricPosition);
}

void Stairs::computeTexture()
{
	Structure::computeTexture();
	auto face = getFace();

	std::string textureName = "stairs_";

	if(face == Directions::EAST) {
		textureName += "east";
	} else if(face == Directions::NORTH) {
		textureName +=  "north";
	} else if(face == Directions::WEST) {
		textureName += "west";
	} else if(face == Directions::SOUTH) {
		textureName += "south";
	}

	if(isFlatMode()) {
		textureName += "_flat";
	}

	spriteComponent_->setTexture(TextureManager::getInstance()->getTexture(textureName));
}

void Stairs::flatModeChanged()
{
	computeTexture();
}

}