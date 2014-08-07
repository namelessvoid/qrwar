#include <stdio.h>

#include "engine/unit.hpp"
#include "engine/square.hpp"
#include "engine/terrain.hpp"

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

	Player* Unit::getPlayer()
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

	int Unit::getAttack()
	{
		return attackvalue;
	}
	int Unit::getDefense()
	{
		return defensevalue;
	}
	int Unit::getHP()
	{
		return hp;
	}
	void Unit::setHP(int hp)
	{
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

	// void Unit::move(int distance)
	// {
	// 	currentmovement -= distance;
	// 	if(currentmovement == 0)
	// 		currentmovement = 0;
	// }
}
