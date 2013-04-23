#include "engine/player.hpp"

namespace qrw
{
	Player::Player()
	:	name("Player")
	{
		for(int i = 0; i < EUT_NUMBEROFUNITTYPES; ++i)
			numberofunits[i] = 0;
	}

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

	void Player::addUnit(Unit* unit)
	{
		unit->setPlayer(this);
		units.push_back(unit);
		++numberofunits[unit->getType()];
	}
}