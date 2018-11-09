#include "game/skirmish/deployladderability.hpp"

#include "engine/board.hpp"
#include "gui/scene.hpp"
#include "gui/squaremarker.hpp"
#include "game/skirmish/laddercarrier.hpp"
#include "game/skirmish/wall.hpp"
#include "game/skirmish/ladder.hpp"

namespace qrw
{

DeployLadderAbility::DeployLadderAbility(Unit* owner)
	: UnitAbility(owner)
{
		setName("Deploy Ladder");

		deploySymbol_ = g_scene.spawn<SquareMarker>();
		deploySymbol_->setVisible(false);
		deploySymbol_->markDeployLadder();
}

void DeployLadderAbility::activate()
{
	UnitAbility::activate();
	deploySymbol_->setVisible(true);
}

void DeployLadderAbility::deactivate()
{
	UnitAbility::deactivate();
	deploySymbol_->setVisible(false);
}

void DeployLadderAbility::updateActiveVisualization(const Coordinates& position)
{
	deploySymbol_->setBoardPosition(position);
}

void DeployLadderAbility::executeOn(const Coordinates& position)
{
	Board* board = g_scene.findSingleGameObject<Board>();
	if(!board) return;

	Ladder* ladder = g_scene.spawn<Ladder>();
	ladder->setPosition(owner_->getPosition());
	ladder->setFace(position - ladder->getPosition());
	board->setStructure(ladder->getPosition(), ladder);

	setEnabled(false);
	deactivate();

	LadderDeployedEvent ladderDeployedEvent;
	owner_->handleEvent(ladderDeployedEvent);
}

bool DeployLadderAbility::canBeExecutedOn(const Coordinates& position)
{
	if(!UnitAbility::canBeExecutedOn(position)) return false;

	Board* board = g_scene.findSingleGameObject<Board>();
	assert(board != nullptr);

	return owner_->getPosition().distanceTo(position) == 1
	&& board->getStructure(owner_->getPosition()) == nullptr
	&& dynamic_cast<Wall*>(board->getStructure(position)) != nullptr;
}

template<>
const SID EventBase<LadderDeployedEvent>::name("SKIRMISH_LADDER_DEPLOYED");

} // namespace qrw
