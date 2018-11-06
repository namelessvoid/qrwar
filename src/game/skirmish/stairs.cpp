#include "game/skirmish/stairs.hpp"

#include "gui/texturemanager.hpp"
#include "foundation/spritecomponent.hpp"
#include "game/constants.hpp"

namespace qrw
{

SID Stairs::typeName("qrw::Stairs");

Stairs::Stairs()
{
	spriteComponent_->setTexture(TextureManager::getInstance()->getTexture("stairs"));
}

}