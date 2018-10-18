#include "game/skirmish/ladder.hpp"

#include "foundation/spritecomponent.hpp"

#include "gui/texturemanager.hpp"

namespace qrw
{

Ladder::Ladder()
{
	spriteComponent_->setTexture(TextureManager::getInstance()->getTexture("ladder"));
}

} // namespace qrw