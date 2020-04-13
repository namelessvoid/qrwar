#include "game/skirmish/deployladderability.hpp"

#include "engine/board.hpp"

#include "gui/scene.hpp"
#include "gui/texturemanager.hpp"

#include "game/renderlayers.hpp"
#include "game/constants.hpp"
#include "game/skirmish/isometricconversion.hpp"
#include "game/skirmish/laddercarrier.hpp"
#include "game/skirmish/wall.hpp"
#include "game/skirmish/ladder.hpp"

namespace qrw
{

DeployLadderAbility::DeployLadderAbility(Unit* owner)
	: UnitAbility(owner)
{
	setName("Deploy Ladder");

	deploySymbol_ = std::make_unique<SpriteComponent>(RENDER_LAYER_CURSOR);
	deploySymbol_->setTexture(TextureManager::getInstance()->getTexture("squaremarkerdeployladder"));
	deploySymbol_->setSize({SQUARE_DIMENSION, SQUARE_DIMENSION});
	deploySymbol_->setOrigin(0.5f * SQUARE_DIMENSION, 0.0f);
	deploySymbol_->setVisible(false);
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
	deploySymbol_->setPosition(worldToIso({SQUARE_DIMENSION * position.getX(), SQUARE_DIMENSION * position.getY()}));
}

void DeployLadderAbility::executeOn(const Coordinates& position)
{
	Board* board = g_scene.findSingleGameObject<Board>();
	if(!board) return;

	Ladder* ladder = g_scene.spawn<Ladder>();
	ladder->setPosition(owner_->getBoardPosition());
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

	return owner_->getBoardPosition().distanceTo(position) == 1
	&& board->getStructure(owner_->getBoardPosition()) == nullptr
	&& dynamic_cast<Wall*>(board->getStructure(position)) != nullptr;
}

template<>
const SID EventBase<LadderDeployedEvent>::name("SKIRMISH_LADDER_DEPLOYED");

} // namespace qrw
