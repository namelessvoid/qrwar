#include "game/skirmish/unit.hpp"

#include "engine/board.hpp"
#include "engine/terrain.hpp"
#include "engine/player.hpp"

#include "foundation/spritecomponent.hpp"
#include "foundation/followrouteanimationcomponent.hpp"
#include "gui/scene.hpp"

#include "gui/texturemanager.hpp"

#include "game/renderlayers.hpp"
#include "game/constants.hpp"
#include "game/damagenumber.hpp"
#include "game/path.hpp"
#include "game/skirmish/wall.hpp"
#include "game/skirmish/unitmovementability.hpp"
#include "game/skirmish/unitmeleeattackability.hpp"
#include "game/skirmish/isometricconversion.hpp"
#include "game/skirmish/boardtoworldconversion.hpp"

namespace qrw
{

Unit::Unit()
	: EventHandler(EventHandlerPriority::DEFAULT)
{
	_sprite = new SpriteComponent(RENDER_LAYER_GAME);
	addComponent(_sprite);
	_sprite->setSize({SQUARE_DIMENSION, SQUARE_DIMENSION});
	_sprite->setOrigin(SQUARE_DIMENSION * 0.5f, 0);

	followRouteAnimationComponent_ = new FollowRouteAnimationComponent(this);
	addComponent(followRouteAnimationComponent_);

	movementAbility_ = new UnitMovementAbility(this);
	addComponent(movementAbility_);
	addAbility(movementAbility_);

	attackAbility_ = new UnitMeleeAttackAbility(this);
	addComponent(attackAbility_);
	addAbility(attackAbility_);
}

void Unit::onDestroy()
{
	Board* board = g_scene.findSingleGameObject<Board>();
	if(board && board->getUnit(_boardPosition) == this)
		board->removeUnit(_boardPosition);

	// Trigger destruction of abilities
	specialAbilities_.clear();
}

Player::Ptr Unit::getPlayer() const
{
	return _player;
}

UNITTYPES Unit::getType() const
{
	return _type;
}

int Unit::getBaseAttack() const
{
	return _attackvalue;
}

int Unit::getModifiedAttack()
{
	int modifiedAttack = getBaseAttack();

	Board* board = g_scene.findSingleGameObject<Board>();
	if(board && board->isTerrainAt(getBoardPosition()))
		modifiedAttack += board->getTerrain(getBoardPosition())->getModificator(EM_ATTACK);

	return modifiedAttack < 0 ? 0 : modifiedAttack;
}

int Unit::getBaseDefense() const
{
	return _defensevalue;
}

int Unit::getModifiedDefense()
{
	int modifiedDefense = getBaseDefense();

	Board* board = g_scene.findSingleGameObject<Board>();
	if(board && board->isTerrainAt(getBoardPosition()))
		modifiedDefense += board->getTerrain(getBoardPosition())->getModificator(EM_DEFENSE);

	return modifiedDefense < 0 ? 0 : modifiedDefense;
}

int Unit::getCurrentHp() const
{
	return _hp;
}

void Unit::setCurrentHp(int hp)
{
	// Prevent hp falling below 0.
	hp = hp < 0 ? 0 : hp;
	this->_hp = hp;
}

int Unit::getMaxHp() const
{
	return _maxhp;
}

void Unit::damage(int inflictedDamage)
{
	setCurrentHp(getCurrentHp() - inflictedDamage);
	if(getCurrentHp() <= 0) g_scene.destroy(this);

	DamageNumber* damageNumber = g_scene.spawn<DamageNumber>();
	damageNumber->setPosition(_sprite->getPosition());
	damageNumber->setDamage(inflictedDamage);
}

int Unit::getMovement() const
{
	return _movement;
}
int Unit::getCurrentMovement() const
{
	return _currentmovement;
}

void Unit::setWorldPosition(const sf::Vector2f& worldPosition)
{
	auto isoPosition = worldToIso(worldPosition);
	auto zIndex = worldToIso(boardToWorld(worldToBoard(worldPosition))).y;

	// Account structures at provided worldPosition
	Coordinates boardPosition = worldToBoard(worldPosition);
	Board* board = g_scene.findSingleGameObject<Board>();
	if(auto structure = board->getStructure(boardPosition)) {
		if(dynamic_cast<Wall*>(structure) != nullptr) {
			isoPosition.y -= 2.0f * SQUARE_DIMENSION;

			// Rather hacky way to get unit rendered before walls when moving from one wall to the other.
			// This will probably break as soon as merlons are added to walls.
			zIndex += 0.2f + SQUARE_DIMENSION;
		}
	}

	_sprite->setPosition(isoPosition);
	_sprite->setZIndex(zIndex);
}

const sf::Vector2f& Unit::getWorldPosition() const
{
	return worldPosition_;
}

const Coordinates& Unit::getBoardPosition() const
{
	return _boardPosition;
}

void Unit::setTexture(const sf::Texture *texture)
{
	_sprite->setTexture(texture);
}

void Unit::setCurrentMovement(int movement)
{
	if(movement < 0)
		_currentmovement = 0;
	else if(movement > this->_movement)
		_currentmovement = this->_movement;
	else
		_currentmovement = movement;
}

void Unit::setBoardPosition_(const Coordinates& boardPosition)
{
	Board* board = g_scene.findSingleGameObject<Board>();
	if (board->getUnit(_boardPosition) == this)
		board->removeUnit(_boardPosition);

	_boardPosition = boardPosition;
	board->setUnit(_boardPosition, this);
}

void Unit::move(const Path& path)
{
	setBoardPosition_(path.last());

	for(int i = 0; i < path.getLength(); ++i) {
		// Skip current start position on running animation since it is already
		// part of the animation (animation.last_step == path.first_step)
		if (followRouteAnimationComponent_->isRunning() && i == 0) continue;

		const Coordinates& step = path.getStep(i);
		followRouteAnimationComponent_->addCorner(boardToWorld(step));
	}

	if(!followRouteAnimationComponent_->isRunning())
		followRouteAnimationComponent_->start();
}

void Unit::deploy(const Coordinates& boardPosition)
{
	setBoardPosition_(boardPosition);

	auto worldPosition = boardToWorld(boardPosition);
	setWorldPosition(worldPosition);
}

UnitAbility* Unit::updateAbilitiesToTarget(const Coordinates& boardPosition)
{
	UnitAbility* activeAbility = nullptr;
	for(auto& ability : specialAbilities_)
	{
		if(!activeAbility && ability->canBeExecutedOn(boardPosition))
		{
			ability->activate();
			ability->updateActiveVisualization(boardPosition);
			activeAbility = ability;
		}
		else
			ability->deactivate();
	}
	return activeAbility;
}

void Unit::deactivateAllAbilities()
{
	for(auto& ability : specialAbilities_)
		ability->deactivate();
}

bool Unit::tryExecuteAbility(const Coordinates& boardPosition)
{
	for(auto& ability : specialAbilities_)
	{
		if(ability->canBeExecutedOn(boardPosition))
		{
			ability->executeOn(boardPosition);
			return true;
		}
	}
	return false;
}

void Unit::addAbility(UnitAbility* ability)
{
	specialAbilities_.push_front(ability);
}

bool Unit::handleEvent(const IEvent& event)
{
	return false;
}

} // namespace qrw
