#include <stdio.h>

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
		clearUnits();
	}

	std::string Player::getName()
	{
		return name;
	}

	void Player::setName(std::string name)
	{
		this->name = name;
	}
	
	int Player::getId()
	{
		return id;
	}

	void Player::setId(int id)
	{
		this->id = id;
	}
	std::vector<Unit*> Player::getUnits()
	{
		return units;
	}

	void Player::addUnit(Unit* unit)
	{
		unit->setPlayer(this);
		units.push_back(unit);
		++numberofunits[unit->getType()];
	}

	int* Player::getNumberOfUnits()
	{
		return numberofunits;
	}

	void Player::clearUnits()
	{
		for(int i = 0; i < EUT_NUMBEROFUNITTYPES; ++i)
			numberofunits[i] = 0;

		for(std::vector<Unit*>::iterator i = units.begin();
			i != units.end(); ++i)
		{
			delete *i;
			// units.erase(i);
		}
		units.clear();
	}
}