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

namespace qrw
{

Unit::Unit()
{
	_sprite = new SpriteComponent(RENDER_LAYER_UNIT);
	addComponent(_sprite);
	_sprite->setSize({SQUARE_DIMENSION, SQUARE_DIMENSION});

	followRouteAnimationComponent_ = new FollowRouteAnimationComponent(_sprite);
	addComponent(followRouteAnimationComponent_);
}

void Unit::onDestroy()
{
	Board* board = g_scene.findSingleGameObject<Board>();
	if(board && board->getUnit(_position) == this)
		board->removeUnit(_position);
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

int Unit::getHP() const
{
	return _hp;
}

void Unit::setHP(int hp)
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
	setHP(getHP() - inflictedDamage);

	DamageNumber* damageNumber = g_scene.spawn<DamageNumber>();
	damageNumber->setPosition(_sprite->getPosition() + sf::Vector2f{16, -16});
	damageNumber->setDamage(inflictedDamage);
}

int Unit::getAttackRange() const
{
	return _range;
}

bool Unit::isTargetWithinAttackRange(const Coordinates &target) const
{
	return getPosition().distanceTo(target) <= getAttackRange();
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

	for(auto& step : path)
	{
		followRouteAnimationComponent_->addEdge(sf::Vector2f{step.getX() * SQUARE_DIMENSION, step.getY() * SQUARE_DIMENSION});
	}
	followRouteAnimationComponent_->start();
}

} // namespace qrw
