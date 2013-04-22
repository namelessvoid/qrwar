#include "engine/player.hpp"

namespace qrw
{
	Player::Player()
	:	name("Player")
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

	std::string Player::getName()
	{
		return name;
	}

	void Player::setName(std::string name)
	{
		this->name = name;
	}
	
	std::vector<Unit*>& Player::getUnits()
	{
		return units;
	}
}