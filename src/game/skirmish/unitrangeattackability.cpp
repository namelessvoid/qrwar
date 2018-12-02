#include "game/skirmish/unitrangeattackability.hpp"

#include "gui/scene.hpp"
#include "gui/texturemanager.hpp"

#include "foundation/spritecomponent.hpp"

#include "game/skirmish/unit.hpp"
#include "game/skirmish/isometricconversion.hpp"
#include "game/renderlayers.hpp"
#include "game/constants.hpp"

namespace qrw
{

UnitRangeAttackAbility::UnitRangeAttackAbility(Unit* owner)
	: UnitAbility(owner),
	  minRange_(2),
	  maxRange_(4),
	  damage_(2)
{
	setName("Ranged Attack");

	squareMarker_ = std::make_unique<SpriteComponent>(RENDER_LAYER_CURSOR);
	squareMarker_->setTexture(TextureManager::getInstance()->getTexture("squaremarkerrangeattack"));
	squareMarker_->setSize({SQUARE_DIMENSION, SQUARE_DIMENSION});
	squareMarker_->setOrigin(0.5f * SQUARE_DIMENSION, 0.0f);
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
	squareMarker_->setPosition(worldToIso({SQUARE_DIMENSION * position.getX(), SQUARE_DIMENSION * position.getY()}));
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
