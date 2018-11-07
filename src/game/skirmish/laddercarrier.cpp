#include "game/skirmish/laddercarrier.hpp"

#include "gui/texturemanager.hpp"

#include "foundation/spritecomponent.hpp"

#include "game/skirmish/deployladderability.hpp"
#include "game/skirmish/unitmeleeattackability.hpp"

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
	addAbility(deployLadderAbility_);

	attackAbility_->setEnabled(false);
}

void LadderCarrier::onAddToScene()
{
	assert(getPlayer() != nullptr);

	GameObject::onAddToScene();
	updateTexture();
}

void LadderCarrier::updateTexture()
{
	std::string playerNumber = std::to_string(getPlayer()->getId());
	const sf::Texture* texture;

	if(deployLadderAbility_->isEnabled())
		texture = TextureManager::getInstance()->getTexture("p" + playerNumber + "laddercarrier");
	else
		texture = TextureManager::getInstance()->getTexture("p" + playerNumber + "laddercarrier_noladder");

	_sprite->setTexture(texture);
}

bool LadderCarrier::handleEvent(const IEvent& event)
{
	if(Unit::handleEvent(event))
		return true;

	if(event.getName() == LadderDeployedEvent::name) {
		updateTexture();
		attackAbility_->setEnabled(true);
		return true;
	}
	return false;
}

} // namespace qrw