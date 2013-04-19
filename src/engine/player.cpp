#include "engine/player.hpp"

namespace qrw
{
	Player::Player()
	{}

	Player::~Player()
	{
		for(std::vector<Unit*>::iterator i = units.begin();
			i != units.end(); ++i)
		{
			delete *i;
			units.erase(i);
		}
	}

	std::vector<Unit*>& Player::getUnits()
	{
		return units;
	}
}