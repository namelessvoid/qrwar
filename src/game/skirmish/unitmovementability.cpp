#include "game/skirmish/unitmovementability.hpp"

#include "gui/scene.hpp"
#include "game/skirmish/unit.hpp"
#include "game/path.hpp"

namespace qrw
{

UnitMovementAbility::UnitMovementAbility(Unit* owner)
	: UnitAbility(owner)
{
	setName("Move");
	path_ = g_scene.spawn<Path>();
}

void UnitMovementAbility::executeOn(const Coordinates& position)
{
	path_->setStartAndEnd(unit_->getBoardPosition(), position);

	int remainingMovement = unit_->getCurrentMovement() - path_->getMovementCosts();
	unit_->setCurrentMovement(remainingMovement);
	unit_->move(*path_);

	path_->reset();
}

bool UnitMovementAbility::canBeExecutedOn(const Coordinates& position)
{
	if(!UnitAbility::canBeExecutedOn(position)) return false;

	Board* board = g_scene.findSingleGameObject<Board>();
	if(!board) return false;

	std::unique_ptr<pathfinding::Path> intermediatePath(board->findPath(unit_->getBoardPosition(), position));
	if(!intermediatePath) return false;

	return intermediatePath->getMovementCosts() <= unit_->getCurrentMovement();
}

void UnitMovementAbility::deactivate()
{
	UnitAbility::deactivate();
	path_->reset();
}

void UnitMovementAbility::updateActiveVisualization(const Coordinates& position)
{
	path_->setStartAndEnd(unit_->getBoardPosition(), position);
}

void UnitMovementAbility::onDestroy()
{
	if(path_) g_scene.destroy(path_);
	GameComponent::onDestroy();
}

}