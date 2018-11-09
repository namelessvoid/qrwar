#include <cstdio>

#include "game/skirmish/unit.hpp"

#include "engine/board.hpp"
#include "engine/terrain.hpp"
#include "engine/player.hpp"

#include "foundation/spritecomponent.hpp"
#include "foundation/followrouteanimationcomponent.hpp"
#include "gui/scene.hpp"

#include "gui/guihelper.hpp"
#include "gui/texturemanager.hpp"

#include "game/renderlayers.hpp"
#include "game/constants.hpp"
#include "game/damagenumber.hpp"
#include "game/path.hpp"
#include "game/skirmish/unitmovementability.hpp"
#include "game/skirmish/unitmeleeattackability.hpp"

namespace qrw
{

Unit::Unit()
	: EventHandler(EventHandlerPriority::DEFAULT)
{
	_sprite = new SpriteComponent(RENDER_LAYER_UNIT);
	addComponent(_sprite);
	_sprite->setSize({SQUARE_DIMENSION, SQUARE_DIMENSION});

	followRouteAnimationComponent_ = new FollowRouteAnimationComponent(_sprite);
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
	if(board && board->getUnit(_position) == this)
		board->removeUnit(_position);

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
	if(board && board->isTerrainAt(getPosition()))
		modifiedAttack += board->getTerrain(getPosition())->getModificator(EM_ATTACK);

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
	if(board && board->isTerrainAt(getPosition()))
		modifiedDefense += board->getTerrain(getPosition())->getModificator(EM_DEFENSE);

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
	damageNumber->setPosition(_sprite->getPosition() + sf::Vector2f{16, -16});
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

const Coordinates& Unit::getPosition() const
{
	return _position;
}

void Unit::setPosition(const Coordinates& position)
{
	setPosition_(position);
	_sprite->setPosition({SQUARE_DIMENSION * _position.getX(), SQUARE_DIMENSION * _position.getY()});
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

void Unit::setPosition_(const Coordinates& position)
{
	Board* board = g_scene.findSingleGameObject<Board>();
	if (board->getUnit(_position) == this)
		board->removeUnit(_position);

	_position = position;
	board->setUnit(_position, this);
}

void Unit::move(const Path& path)
{
	setPosition_(path.last());

	for(int i = 0; i < path.getLength(); ++i)
	{
		// Skip current start position on running animation since it is already
		// part of the animation (animation.last_step == path.first_step)
		if(followRouteAnimationComponent_->isRunning() && i == 0) continue;

		const Coordinates& step = path.getStep(i);
		followRouteAnimationComponent_->addCorner(sf::Vector2f{step.getX() * SQUARE_DIMENSION, step.getY() * SQUARE_DIMENSION});
	}

	if(!followRouteAnimationComponent_->isRunning())
		followRouteAnimationComponent_->start();
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
