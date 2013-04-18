#include "engine/unit.hpp"

namespace qrw
{
	Unit::Unit(std::string name, int attack, int defense,
				int range, Player* player)
	:	name(name),
		attack(attack),
		defense(defense),
		range(range),
		player(player)
	{}

	Unit::~Unit()
	{}

	Player* Unit::getPlayer()
	{
		return player;
	}
}