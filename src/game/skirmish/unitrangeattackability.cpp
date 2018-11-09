#include "game/skirmish/unitrangeattackability.hpp"

#include "game/skirmish/unit.hpp"

#include "gui/scene.hpp"

namespace qrw
{

UnitRangeAttackAbility::UnitRangeAttackAbility(Unit* owner)
	: UnitAbility(owner),
	  minRange_(2),
	  maxRange_(4),
	  damage_(2)
{
	setName("Ranged Attack");

	squareMarker_ = g_scene.spawn<SquareMarker>();
	squareMarker_->markRangeAttackable();
	squareMarker_->setVisible(false);
}

void UnitRangeAttackAbility::executeOn(const Coordinates& position)
{
	Board* board = g_scene.findSingleGameObject<Board>();
	assert(board);

	Unit* opponent = board->getUnit(position);
	assert(opponent);

	opponent->damage(damage_);

	owner_->setCurrentMovement(0);
}

void UnitRangeAttackAbility::activate()
{
	UnitAbility::activate();
	squareMarker_->setVisible(true);
}

void UnitRangeAttackAbility::deactivate()
{
	UnitAbility::deactivate();
	squareMarker_->setVisible(false);
}

void UnitRangeAttackAbility::updateActiveVisualization(const Coordinates& position)
{
	squareMarker_->setBoardPosition(position);
}

bool UnitRangeAttackAbility::canBeExecutedOn(const Coordinates& position)
{
	if(!UnitAbility::canBeExecutedOn(position)) return false;

	unsigned int distanceToTarget = owner_->getPosition().distanceTo(position);
	if(distanceToTarget < minRange_ || distanceToTarget > maxRange_) return false;

	if(owner_->getCurrentMovement() <= 0) return false;

	Board* board = g_scene.findSingleGameObject<Board>();
	assert(board != nullptr);

	Unit* opponent = board->getUnit(position);
	if(!opponent || owner_->getPlayer() == opponent->getPlayer()) return false;

	return true;
}

} //namespace qrw
