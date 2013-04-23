#include "engine/unit.hpp"

namespace qrw
{
	Unit::Unit(UNITTYPES type, int attack, int defense,
				int range, int movement, Player* player)
	:	type(type),
		attack(attack),
		defense(defense),
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
		return attack;
	}
	int Unit::getDefense()
	{
		return defense;
	}
	int Unit::getHP()
	{
		return hp;
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
	// void Unit::move(int distance)
	// {
	// 	currentmovement -= distance;
	// 	if(currentmovement == 0)
	// 		currentmovement = 0;
	// }
}