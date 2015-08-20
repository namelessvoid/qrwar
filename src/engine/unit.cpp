#include <stdio.h>

#include "engine/unit.hpp"
#include "engine/board.hpp"
#include "engine/square.hpp"
#include "engine/terrain.hpp"
#include "engine/player.hpp"
#include "engine/pathfinding/path.hpp"

namespace qrw
{
	std::string Unit::UNITNAMES[] =
	{
		"Swordman", "Archer", "Spearman"
	};

	Unit::Unit(UNITTYPES type, int hp, int attack, int defense,
				int range, int movement, Player* player, Board* board)
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
	}

	Unit::~Unit()
	{}

	Player* Unit::getPlayer() const
	{
		return _player;
	}
	void Unit::setPlayer(Player* player)
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

		if(_square->getTerrain())
			modifiedAttack += _square->getTerrain()->getModificator(EM_ATTACK);

		return modifiedAttack < 0 ? 0 : modifiedAttack;
	}

	int Unit::getBaseDefense()
	{
		return _defensevalue;
	}

	int Unit::getModifiedDefense()
	{
		int modifiedDefense = getBaseDefense();

		if(_square->getTerrain())
			modifiedDefense += _square->getTerrain()->getModificator(EM_DEFENSE);

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
	int Unit::getRange()
	{
		return _range;
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

	void Unit::setCurrentMovement(int movement)
	{
		if(movement < 0)
			_currentmovement = 0;
		else if(movement > this->_movement)
			_currentmovement = this->_movement;
		else
			_currentmovement = movement;
	}

	Square* Unit::getSquare() const
	{
		return _square;
	}

	void Unit::setSquare(Square* square)
	{
		this->_square = square;
	}

	void Unit::removeFromBoard()
	{
		if(_square)
		{
			_square->setUnit(nullptr);
			_square = nullptr;
		}
	}

	Path* Unit::canMoveTo(const Coordinates& destination)
	{
		if(!_player->isActive())
			return nullptr;

		if(_board->getSquare(destination)->getUnit())
			return nullptr;

		Path* path = _board->findPath(_square->getCoordinates(), destination);

		if(path->getMovementCosts() > getCurrentMovement())
		{
			delete path;
			return nullptr;
		}

		return path;
	}

	bool Unit::moveTo(const Coordinates& destination)
	{
		Path* path = canMoveTo(destination);
		if(!path)
			return false;

		_square->setUnit(nullptr);
		this->setSquare(_board->getSquare(destination));
		_square->setUnit(this);
		this->setCurrentMovement(this->getCurrentMovement() - path->getMovementCosts());

		delete path;

		return true;
	}

	bool Unit::canAttack(const Unit* const enemy)
	{
		if(!_player->isActive())
			return false;

		if(!this->getCurrentMovement() > 0)
			return false;

		if(enemy->getPlayer() == this->getPlayer())
			return false;

		int distance = this->_square->getDistance(enemy->getSquare());
		if(distance > this->getRange())
			return false;

		return true;
	}

	Unit::AttackResult Unit::attack(Unit* enemy)
	{
		AttackResult attackResult;

		if(!canAttack(enemy))
		{
			attackResult.attackPerformed = false;
			return attackResult;
		}

		this->setCurrentMovement(0);

		// Attack and counter attack
		attackResult.defenderHPDelta = this->doAttack(enemy);
		attackResult.attackerHPDelta = enemy->doAttack(this);

		attackResult.attackPerformed = true;
		return attackResult;
	}

	int Unit::doAttack(Unit* enemy)
	{
		if(this->getHP() == 0)
			return 0;

		int damage = this->getModifiedAttack() - enemy->getModifiedDefense();
		damage = damage < 0 ? 0 : damage;

		enemy->setHP(enemy->getHP() - damage);
		if(enemy->getHP() == 0)
			enemy->removeFromBoard();

		return damage;
	}

	// void Unit::move(int distance)
	// {
	// 	currentmovement -= distance;
	// 	if(currentmovement == 0)
	// 		currentmovement = 0;
	// }
}
