#include <game/skirmish/structureaccessibilitychecker.hpp>
#include "game/skirmish/unitattackability.hpp"

#include "gui/scene.hpp"

#include "engine/board.hpp"
#include "game/skirmish/unit.hpp"

namespace qrw
{

UnitAttackAbility::UnitAttackAbility(Unit* owner) : UnitAbility(owner)
{
	setName("Attack");
}

void UnitAttackAbility::executeOn(const Coordinates& position)
{
	Unit* opponent = getOpponentAt(position);
	if(!opponent) return;

	owner_->setCurrentMovement(0);

	inflictDamage(*opponent);
	if(opponent->getHP() <= 0)
		return;

	UnitAttackAbility* opponentAttackAbility = opponent->getComponent<UnitAttackAbility>();
	opponentAttackAbility->counterAttack(*owner_);
}

void UnitAttackAbility::counterAttack(Unit& opponent)
{
	if(!isEnabled()) return;

	inflictDamage(opponent);
}

void UnitAttackAbility::inflictDamage(Unit& opponent)
{
	int inflictedDamage = owner_->getModifiedAttack() - opponent.getModifiedDefense();
	inflictedDamage = inflictedDamage < 0 ? 0 : inflictedDamage;
	opponent.damage(inflictedDamage);
}

bool UnitAttackAbility::canBeExecutedOn(const Coordinates& position)
{
	if(!UnitAbility::canBeExecutedOn(position)) return false;

	if(!getOpponentAt(position)) return false;
	if(owner_->getCurrentMovement() <= 0) return false;

	StructureAccessibilityChecker structureAccessibilityChecker;
	return structureAccessibilityChecker.isAccessible(owner_->getPosition(),
													  position,
													  *g_scene.findSingleGameObject<qrw::Board>());
}

Unit* UnitAttackAbility::getOpponentAt(const Coordinates& position)
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