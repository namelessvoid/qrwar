#include "game/skirmish/structure.hpp"

#include "foundation/spritecomponent.hpp"

#include "game/renderlayers.hpp"
#include "game/constants.hpp"

#include "gui/texturemanager.hpp"

namespace qrw
{

SID Structure::typeName("qrw::Structure");

Structure::Structure()
{
	spriteComponent_ = new SpriteComponent(RENDER_LAYER_STRUCTURE);
	spriteComponent_->setSize({SQUARE_DIMENSION, SQUARE_DIMENSION});
	spriteComponent_->setTexture(TextureManager::getInstance()->getTexture("wall"));
	addComponent(spriteComponent_);
}

void Structure::setPosition(const Coordinates& position)
{
	position_ = position;
	spriteComponent_->setPosition({SQUARE_DIMENSION * position_.getX(), SQUARE_DIMENSION * position.getY()});
}

} // namespace qrw
