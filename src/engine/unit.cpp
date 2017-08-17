#include <stdio.h>

#include "engine/unit.hpp"
#include "engine/board.hpp"
#include "engine/terrain.hpp"
#include "engine/player.hpp"
#include "engine/pathfinding/path.hpp"

#include "foundation/spritecomponent.hpp"
#include "gui/scene.hpp"

#include "gui/guihelper.hpp"
#include "gui/texturemanager.hpp"

#include "game/renderlayers.hpp"
#include "game/damagenumber.hpp"

namespace qrw
{

const float Unit::_dimension = 32;

std::string Unit::UNITNAMES[] =
{
	"Swordman", "Archer", "Spearman"
};

Unit::Unit(UNITTYPES type, int hp, int attack, int defense,
			int range, int movement, Player::Ptr player,
			const sf::Texture* texture)
:	_type(type),
	_hp(hp),
	_maxhp(hp),
	_attackvalue(attack),
	_defensevalue(defense),
	_range(range),
	_movement(movement),
	_currentmovement(movement),
	_player(player)
{
	_sprite = new SpriteComponent(RENDER_LAYER_UNIT);
	addComponent(_sprite);
	_sprite->setSize(sf::Vector2f(_dimension, _dimension));
	_sprite->setTexture(texture);
}

Unit* Unit::createUnit(UNITTYPES unitType, Player::Ptr player)
{
	const sf::Texture* texture = GuiHelper::getUnitTexture(unitType, player);

	switch(unitType)
	{
	case EUT_SWORDMAN:
		return new Unit(EUT_SWORDMAN, 5, 2, 1, 1, 3, player, texture);
	case EUT_ARCHER:
		return new Unit(EUT_ARCHER, 5, 2, 1, 2, 2, player, texture);
	default:
		return new Unit(EUT_SPEARMAN, 5, 2, 1, 1, 2, player, texture);
	}
}

Unit::~Unit()
{
	Board* board = g_scene.getSingleGameObject<Board>();
	if(board->getUnit(_position) == this)
		board->removeUnit(_position);

	g_scene.removeGameObject(this);
}

Player::Ptr Unit::getPlayer() const
{
	return _player;
}

void Unit::setPlayer(Player::Ptr player)
{
	this->_player = player;
}

UNITTYPES Unit::getType()
{
	return _type;
}

int Unit::getBaseAttack()
{
	return _attackvalue;
}

int Unit::getModifiedAttack()
{
	int modifiedAttack = getBaseAttack();

	Board* board = g_scene.getSingleGameObject<Board>();
	if(board && board->isTerrainAt(getPosition()))
		modifiedAttack += board->getTerrain(getPosition())->getModificator(EM_ATTACK);

	return modifiedAttack < 0 ? 0 : modifiedAttack;
}

int Unit::getBaseDefense()
{
	return _defensevalue;
}

int Unit::getModifiedDefense()
{
	int modifiedDefense = getBaseDefense();

	Board* board = g_scene.getSingleGameObject<Board>();
	if(board && board->isTerrainAt(getPosition()))
		modifiedDefense += board->getTerrain(getPosition())->getModificator(EM_DEFENSE);

	return modifiedDefense < 0 ? 0 : modifiedDefense;
}

int Unit::getHP()
{
	return _hp;
}

void Unit::setHP(int hp)
{
	// Prevent hp falling below 0.
	hp = hp < 0 ? 0 : hp;
	this->_hp = hp;
}

int Unit::getMaxHp()
{
	return _maxhp;
}
void Unit::setMaxHp(int maxhp)
{
	this->_maxhp = maxhp;
}

void Unit::damage(int inflictedDamage)
{
	setHP(getHP() - inflictedDamage);

	DamageNumber* damageNumber = new DamageNumber(inflictedDamage);
	damageNumber->setPosition(_sprite->getPosition() + sf::Vector2f{16, -16});
	g_scene.addGameObject(damageNumber);
}

int Unit::getAttackRange() const
{
	return _range;
}

bool Unit::isTargetWithinAttackRange(const Coordinates &target) const
{
	return getPosition().distanceTo(target) <= getAttackRange();
}

int Unit::getMovement()
{
	return _movement;
}
int Unit::getCurrentMovement()
{
	return _currentmovement;
}
std::string Unit::getName()
{
	return UNITNAMES[_type];
}

const Coordinates& Unit::getPosition() const
{
	return _position;
}

void Unit::setPosition(const Coordinates& position)
{
	Board* board = g_scene.getSingleGameObject<Board>();
	if(board->getUnit(_position) == this)
		board->removeUnit(_position);

	_position = position;
	board->setUnit(_position, this);
	_sprite->setPosition(sf::Vector2f(_dimension * _position.getX(), _dimension * _position.getY()));
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

} // namespace qrw
