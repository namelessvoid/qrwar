#include "game/skirmish/stairs.hpp"

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
	spriteComponent_->setSize({2.0f * SQUARE_DIMENSION, SQUARE_DIMENSION});
	spriteComponent_->setOrigin(SQUARE_DIMENSION, 0);
	spriteComponent_->setTexture(TextureManager::getInstance()->getTexture("stairs"));
	addComponent(spriteComponent_);
}

const sf::Texture* Stairs::getTexture() const
{
	return spriteComponent_->getTexture();
}

}