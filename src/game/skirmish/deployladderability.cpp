#include "game/skirmish/deployladderability.hpp"

#include "engine/board.hpp"
#include "gui/scene.hpp"
#include "game/skirmish/unit.hpp"
#include "game/skirmish/wall.hpp"
#include "game/skirmish/ladder.hpp"

namespace qrw
{

DeployLadderAbility::DeployLadderAbility(Unit* owner)
	: UnitSpecialAbility(owner)
{
		setName("Deploy Ladder");
}

void DeployLadderAbility::executeOn(const Coordinates& position)
{
	Board* board = g_scene.findSingleGameObject<Board>();
	if(!board) return;

	Ladder* ladder = g_scene.spawn<Ladder>();
	ladder->setPosition(owner_->getPosition());
	ladder->setFace(position - ladder->getPosition());
	board->setStructure(ladder->getPosition(), ladder);
}

bool DeployLadderAbility::canBeExecutedOn(const Coordinates& position)
{
	Board* board = g_scene.findSingleGameObject<Board>();
	if(!board) return false;

	return owner_->getPosition().distanceTo(position) == 1
	&& board->getStructure(owner_->getPosition()) == nullptr
	&& dynamic_cast<Wall*>(board->getStructure(position)) != nullptr;
}

} // namespace qrw
