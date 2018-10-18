#include "game/skirmish/laddercarrier.hpp"

#include "gui/texturemanager.hpp"

#include "foundation/spritecomponent.hpp"

#include "game/skirmish/deployladderability.hpp"

namespace qrw
{

LadderCarrier::LadderCarrier()
{
	setType(EUT_LADDERCARRIER);

	setMaxHp(4);
	setHP(4);

	setAttack(2);
	setDefense(0);
	setRange(1);

	setMovement(3);
	setCurrentMovement(3);

	deployLadderAbility_ = new DeployLadderAbility(this);
	addComponent(deployLadderAbility_);
	addSpecialAbility(deployLadderAbility_);
}

void LadderCarrier::onAddToScene()
{
	assert(getPlayer() != nullptr);

	GameObject::onAddToScene();

	std::string playerNumber = std::to_string(getPlayer()->getId());
	_sprite->setTexture(TextureManager::getInstance()->getTexture("p" + playerNumber + "laddercarrier"));
}

} // namespace qrw