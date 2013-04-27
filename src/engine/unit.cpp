#include <stdio.h>

#include "engine/unit.hpp"

namespace qrw
{
	Unit::Unit(UNITTYPES type, int hp, int attack, int defense,
				int range, int movement, Player* player)
	:	type(type),
		hp(hp),
		attackvalue(attack),
		defensevalue(defense),
		range(range),
		movement(movement),
		currentmovement(movement),
		player(player)
	{}

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
	void Unit::setCurrentMovement(int movement)
	{
		if(movement < 0)
			currentmovement = 0;
		else if(movement > this->movement)
			currentmovement = this->movement;
		else
			currentmovement = movement;
	}

	void Unit::attack(Unit* enemy)
	{
		printf("before attack: a(%i), d(%i)\n", getHP(), enemy->getHP());
		// Attacker attacks first
		enemy->setHP(battleHPResult(enemy));
		// Enemy attacks if he's still alive
		if(enemy->getHP() > 0)
			setHP(enemy->battleHPResult(this));
		printf("after attack: a(%i), d(%i)\n", getHP(), enemy->getHP());
	}

	int Unit::battleHPResult(Unit* enemy)
	{
		// Calculate effect on enemy
		int damage = getAttack() - enemy->getDefense();
		if(damage < 0)
			damage = 0;
		int newhp = enemy->getHP() - damage;
		return newhp < 0 ? 0 : newhp;
	}
	// void Unit::move(int distance)
	// {
	// 	currentmovement -= distance;
	// 	if(currentmovement == 0)
	// 		currentmovement = 0;
	// }
}