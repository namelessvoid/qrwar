#include "game/skirmish/archer.hpp"

#include "gui/guihelper.hpp"

#include "foundation/spritecomponent.hpp"

#include "game/skirmish/unitrangeattackability.hpp"

namespace qrw
{

Archer::Archer()
	: Unit()
{
	setType(UNITTYPES::EUT_ARCHER);

	setMaxHp(5);
	setCurrentHp(5);

	setAttack(1);
	setDefense(1);
	setRange(2);
	setMaxMovement(2);
	setCurrentMovement(2);

	UnitRangeAttackAbility* rangeAttackAbility = new UnitRangeAttackAbility(this);
	addComponent(rangeAttackAbility);
	addAbility(rangeAttackAbility);
}

void Archer::onAddToScene()
{
	assert(getPlayer() != nullptr);

	GameObject::onAddToScene();
	_sprite->setTexture(GuiHelper::getUnitTexture(UNITTYPES::EUT_ARCHER, getPlayer()->getId()));
}

} // namespace qrw
