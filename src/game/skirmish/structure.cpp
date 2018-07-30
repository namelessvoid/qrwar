#include "game/skirmish/structure.hpp"

#include "foundation/spritecomponent.hpp"

#include "game/renderlayers.hpp"
#include "game/constants.hpp"

#include "gui/texturemanager.hpp"

namespace qrw
{

Structure::Structure()
{
	SpriteComponent* spriteComponent = new SpriteComponent(RENDER_LAYER_STRUCTURE);
	spriteComponent->setSize({SQUARE_DIMENSION, SQUARE_DIMENSION});
	spriteComponent->setTexture(TextureManager::getInstance()->getTexture("wall"));
	addComponent(spriteComponent);
}

} // namespace qrw
