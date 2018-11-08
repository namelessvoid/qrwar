#include <game/skirmish/structureaccessibilitychecker.hpp>
#include "game/skirmish/unitmeleeattackability.hpp"

#include "gui/scene.hpp"

#include "engine/board.hpp"
#include "game/skirmish/unit.hpp"

namespace qrw
{

UnitMeleeAttackAbility::UnitMeleeAttackAbility(Unit* owner) : UnitAbility(owner)
{
	setName("Attack");
}

void UnitMeleeAttackAbility::executeOn(const Coordinates& position)
{
	Unit* opponent = getOpponentAt(position);
	assert(opponent);

	owner_->setCurrentMovement(0);

	inflictDamage(*opponent);
	if(opponent->getCurrentHp() <= 0)
		return;

	UnitMeleeAttackAbility* opponentAttackAbility = opponent->getComponent<UnitMeleeAttackAbility>();
	opponentAttackAbility->counterAttack(*owner_);
}

void UnitMeleeAttackAbility::counterAttack(Unit& opponent)
{
	if(!isEnabled()) return;

	inflictDamage(opponent);
}

void UnitMeleeAttackAbility::inflictDamage(Unit& opponent)
{
	int inflictedDamage = owner_->getModifiedAttack() - opponent.getModifiedDefense();
	inflictedDamage = inflictedDamage < 0 ? 0 : inflictedDamage;
	opponent.damage(inflictedDamage);
}

bool UnitMeleeAttackAbility::canBeExecutedOn(const Coordinates& position)
{
	if(!UnitAbility::canBeExecutedOn(position)) return false;

	if(!getOpponentAt(position)) return false;
	if(owner_->getCurrentMovement() <= 0) return false;
	if(owner_->getPosition().distanceTo(position) > getAttackRange()) return false;

	StructureAccessibilityChecker structureAccessibilityChecker;
	return structureAccessibilityChecker.isAccessible(owner_->getPosition(),
													  position,
													  *g_scene.findSingleGameObject<qrw::Board>());
}

Unit* UnitMeleeAttackAbility::getOpponentAt(const Coordinates& position)
{
	Board* board = g_scene.findSingleGameObject<Board>();
	if(!board) return nullptr;

	Unit* opponent = board->getUnit(position);
	if(!opponent) return nullptr;

	if(opponent->getPlayer() == owner_->getPlayer())
		return nullptr;

	return opponent;
}

} // namespace qrw