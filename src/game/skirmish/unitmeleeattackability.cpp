#include "game/skirmish/unitmeleeattackability.hpp"

#include "gui/scene.hpp"
#include "gui/texturemanager.hpp"

#include "game/skirmish/structureaccessibilitychecker.hpp"
#include "game/constants.hpp"
#include "game/renderlayers.hpp"
#include "engine/board.hpp"
#include "game/skirmish/unit.hpp"
#include "game/skirmish/isometricconversion.hpp"

namespace qrw
{

UnitMeleeAttackAbility::UnitMeleeAttackAbility(Unit* owner) : UnitAbility(owner)
{
	setName("Attack");

	attackSymbol_ = std::make_unique<SpriteComponent>(RENDER_LAYER_CURSOR);
	attackSymbol_->setVisible(false);
	attackSymbol_->setTexture(TextureManager::getInstance()->getTexture("squaremarkerattack"));
	attackSymbol_->setSize({SQUARE_DIMENSION, SQUARE_DIMENSION});
	attackSymbol_->setOrigin(0.5f * SQUARE_DIMENSION, 0.0f);
}

void UnitMeleeAttackAbility::activate()
{
	UnitAbility::activate();
	attackSymbol_->setVisible(true);
}

void UnitMeleeAttackAbility::deactivate()
{
	UnitAbility::deactivate();
	attackSymbol_->setVisible(false);
}

void UnitMeleeAttackAbility::updateActiveVisualization(const Coordinates& position)
{
	attackSymbol_->setPosition(worldToIso(sf::Vector2f(position.getX(), position.getY()) * SQUARE_DIMENSION));
}

void UnitMeleeAttackAbility::executeOn(const Coordinates& position)
{
	Unit* opponent = getOpponentAt(position);
	assert(opponent);

	owner_->setCurrentMovement(0);

	inflictDamage(*opponent);
	if(opponent->getCurrentHp() <= 0)
		return;

	UnitMeleeAttackAbility* opponentAttackAbility = opponent->getFirstComponent<UnitMeleeAttackAbility>();
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