#include "game/skirmish/unitmovementability.hpp"

#include "gui/scene.hpp"
#include "game/skirmish/unit.hpp"
#include "game/path.hpp"

namespace qrw
{

UnitMovementAbility::UnitMovementAbility(Unit* owner)
	: UnitSpecialAbility(owner)
{
	setName("Move");
	path_ = g_scene.spawn<Path>();
}

void UnitMovementAbility::executeOn(const Coordinates& position)
{
	path_->setStartAndEnd(owner_->getPosition(), position);

	int remainingMovement = owner_->getCurrentMovement() - path_->getMovementCosts();
	owner_->setCurrentMovement(remainingMovement);
	owner_->move(*path_);

	path_->reset();
}

bool UnitMovementAbility::canBeExecutedOn(const Coordinates& position)
{
	if(!UnitSpecialAbility::canBeExecutedOn(position)) return false;

	Board* board = g_scene.findSingleGameObject<Board>();
	if(!board) return false;

	std::unique_ptr<pathfinding::Path> intermediatePath(board->findPath(owner_->getPosition(), position));
	if(!intermediatePath) return false;

	return intermediatePath->getMovementCosts() <= owner_->getCurrentMovement();
}

void UnitMovementAbility::deactivate()
{
	UnitSpecialAbility::deactivate();
	path_->reset();
}

void UnitMovementAbility::updateVisualization(const Coordinates& position)
{
	path_->setStartAndEnd(owner_->getPosition(), position);
}

void UnitMovementAbility::onDestroy()
{
	if(path_) g_scene.destroy(path_);
	GameComponent::onDestroy();
}

}