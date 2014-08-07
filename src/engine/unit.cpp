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
		int modifiedAttack = getBaseAttack() + square->getTerrain()->getModificator(EM_ATTACK);
		return modifiedAttack < 0 ? 0 : modifiedAttack;
	}

	int Unit::getBaseDefense()
	{
		return defensevalue;
	}

	int Unit::getModifiedDefense()
	{
		int modifiedDefense = getBaseDefense() + square->getTerrain()->getModificator(EM_DEFENSE);
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

	void Unit::attack(Unit* enemy, int* attackmods, int* defensemods)
	{
		// Attacker attacks first
		enemy->setHP(battleHPResult(enemy, attackmods[EM_ATTACK],
			defensemods[EM_DEFENSE]));
		// Enemy attacks if he's still alive
		if(enemy->getHP() > 0)
			setHP(enemy->battleHPResult(this, defensemods[EM_ATTACK],
				attackmods[EM_DEFENSE]));
	}

	int Unit::battleHPResult(Unit* enemy, int attackmod, int defensemod)
	{
		// Calculate effect on enemy
		int attack = getAttack() + attackmod;
		if(attack < 0)
			attack = 0;
		int defense = enemy->getDefense() + defensemod;
		if(defense < 0)
			defense = 0;
		int damage = attack - defense;
		if(damage < 0)
			damage = 0;
		int newhp = enemy->getHP() - damage;
		return newhp < 0 ? 0 : newhp;
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
