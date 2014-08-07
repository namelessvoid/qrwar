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
	:	type(type),
		hp(hp),
		maxhp(hp),
		attackvalue(attack),
		defensevalue(defense),
		range(range),
		movement(movement),
		currentmovement(movement),
		player(player),
		board(board)
	{
	}

	Unit::~Unit()
	{}

	Player* Unit::getPlayer() const
	{
		return player;
	}
	void Unit::setPlayer(Player* player)
	{
		this->player = player;
	}
	UNITTYPES Unit::getType()
	{
		return type;
	}

	int Unit::getBaseAttack()
	{
		return attackvalue;
	}

	int Unit::getModifiedAttack()
	{
		int modifiedAttack = getBaseAttack();

		if(square->getTerrain())
			modifiedAttack += square->getTerrain()->getModificator(EM_ATTACK);

		return modifiedAttack < 0 ? 0 : modifiedAttack;
	}

	int Unit::getBaseDefense()
	{
		return defensevalue;
	}

	int Unit::getModifiedDefense()
	{
		int modifiedDefense = getBaseDefense();

		if(square->getTerrain())
			modifiedDefense += square->getTerrain()->getModificator(EM_DEFENSE);

		return modifiedDefense < 0 ? 0 : modifiedDefense;
	}

	int Unit::getHP()
	{
		return hp;
	}

	void Unit::setHP(int hp)
	{
		// Prevent hp falling below 0.
		hp = hp < 0 ? 0 : hp;
		this->hp = hp;
	}

	int Unit::getMaxHp()
	{
		return maxhp;
	}
	void Unit::setMaxHp(int maxhp)
	{
		this->maxhp = maxhp;
	}
	int Unit::getRange()
	{
		return range;
	}
	int Unit::getMovement()
	{
		return movement;
	}
	int Unit::getCurrentMovement()
	{
		return currentmovement;
	}
	std::string Unit::getName()
	{
		return UNITNAMES[type];
	}

	void Unit::setCurrentMovement(int movement)
	{
		if(movement < 0)
			currentmovement = 0;
		else if(movement > this->movement)
			currentmovement = this->movement;
		else
			currentmovement = movement;
	}

	Unit::AttackResult Unit::attack(Unit* enemy, bool allowCounterAttack)
	{
		AttackResult attackResult;

		if(!this->canAttack(enemy))
		{
			attackResult.attackPerformed = false;
			return attackResult;
		}

		// Attacker attacks first
		int damage = this->getModifiedAttack() - enemy->getModifiedDefense();
		damage = damage < 0 ? 0 : damage;

		enemy->setHP(enemy->getHP() - damage);
		attackResult.defenderHPDelta = damage;

		// Counter attack
		if(enemy->getHP() > 0 && allowCounterAttack == true)
		{
			damage = enemy->getModifiedAttack() - this->getModifiedDefense();
			damage = damage < 0 ? 0 : damage;

			this->setHP(this->getHP() - damage);
			attackResult.attackerHPDelta = damage;
		}

		attackResult.attackPerformed = true;
		return attackResult;
	}

	Square* Unit::getSquare() const
	{
		return square;
	}

	void Unit::setSquare(Square* square)
	{
		this->square = square;
	}

	Path* Unit::canMoveTo(const Coordinates& destination)
	{
		if(!player->isActive())
			return nullptr;

		if(board->getSquare(destination)->getUnit())
			return nullptr;

		Path* path = board->findPath(square->getCoordinates(), destination);

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

		square->setUnit(nullptr);
		this->setSquare(board->getSquare(destination));
		square->setUnit(this);
		this->setCurrentMovement(this->getCurrentMovement() - path->getMovementCosts());

		delete path;

		return true;
	}

	bool Unit::canAttack(const Unit* const enemy)
	{
		if(!player->isActive())
			return false;

		if(enemy->getPlayer() == this->getPlayer())
			return false;

		int distance = this->square->getDistance(enemy->getSquare());
		if(distance > this->getRange())
			return false;

		return true;
	}

	// void Unit::move(int distance)
	// {
	// 	currentmovement -= distance;
	// 	if(currentmovement == 0)
	// 		currentmovement = 0;
	// }
}
