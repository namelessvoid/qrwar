#include "game/skirmish/ladder.hpp"

#include "foundation/spritecomponent.hpp"

#include "gui/texturemanager.hpp"

#include "game/constants.hpp"
#include "game/renderlayers.hpp"

namespace qrw
{

Ladder::Ladder()
{
	spriteComponent_ = new SpriteComponent(RENDER_LAYER_GAME);
	spriteComponent_->setSize({2.0f * SQUARE_DIMENSION, SQUARE_DIMENSION});
	spriteComponent_->setOrigin(SQUARE_DIMENSION, 0);
	spriteComponent_->setTexture(TextureManager::getInstance()->getTexture("ladder"));
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

} // namespace qrw