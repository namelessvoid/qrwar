#include <stdio.h>

#include "engine/unit.hpp"
#include "engine/board.hpp"
#include "engine/terrain.hpp"
#include "engine/player.hpp"
#include "engine/pathfinding/path.hpp"

#include "gui/guihelper.hpp"
#include "gui/texturemanager.hpp"

namespace qrw
{

const float Unit::_dimension = 32;

std::string Unit::UNITNAMES[] =
{
	"Swordman", "Archer", "Spearman"
};

Unit::Unit(UNITTYPES type, int hp, int attack, int defense,
			int range, int movement, Player::Ptr player, Board::Ptr board,
			const sf::Texture* texture)
:	_type(type),
	_hp(hp),
	_maxhp(hp),
	_attackvalue(attack),
	_defensevalue(defense),
	_range(range),
	_movement(movement),
	_currentmovement(movement),
	_player(player),
	_board(board)
{
	setSize(sf::Vector2f(_dimension, _dimension));

	setTexture(texture);
}

Unit::Ptr Unit::createUnit(UNITTYPES unitType, Player::Ptr player, Board::Ptr board)
{
	const sf::Texture* texture = GuiHelper::getUnitTexture(unitType, player);

	switch(unitType)
	{
	case EUT_SWORDMAN:
		return Ptr(new Unit(EUT_SWORDMAN, 5, 2, 1, 1, 3, player, board, texture));
	case EUT_ARCHER:
		return Ptr(new Unit(EUT_ARCHER, 5, 2, 1, 3, 2, player, board, texture));
	default:
		return Ptr(new Unit(EUT_SPEARMAN, 5, 2, 1, 2, 2, player, board, texture));
	}
}

Unit::~Unit()
{}

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

	if(_board->isTerrainAt(getPosition()))
		modifiedAttack += _board->getTerrain(getPosition())->getModificator(EM_ATTACK);

	return modifiedAttack < 0 ? 0 : modifiedAttack;
}

int Unit::getBaseDefense()
{
	return _defensevalue;
}

int Unit::getModifiedDefense()
{
	int modifiedDefense = getBaseDefense();

	if(_board->isTerrainAt(getPosition()))
		modifiedDefense += _board->getTerrain(getPosition())->getModificator(EM_DEFENSE);

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
}

int Unit::getRange() const
{
	return _range;
}

bool Unit::isTargetWithinAttackRange(const Coordinates &target) const
{
	return getPosition().distanceTo(target) <= getRange();
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
	_position = position;
	sf::RectangleShape::setPosition(sf::Vector2f(_dimension * _position.getX(), _dimension * _position.getY()));
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

Unit::AttackResult Unit::attack(Unit::Ptr enemy)
{
	AttackResult attackResult;

	this->setCurrentMovement(0);

	// Attack and counter attack
	attackResult.defenderHPDelta = this->doAttack(enemy);
												// Hacky access to shared ptr of this
	attackResult.attackerHPDelta = enemy->doAttack(_board->getUnit(getPosition()));

	attackResult.attackPerformed = true;
	return attackResult;
}

int Unit::doAttack(Unit::Ptr enemy)
{
	if(this->getHP() == 0)
		return 0;

	int damage = this->getModifiedAttack() - enemy->getModifiedDefense();
	damage = damage < 0 ? 0 : damage;

	enemy->setHP(enemy->getHP() - damage);

	return damage;
}

} // namespace qrw
