#include <stdio.h>

#include "engine/player.hpp"

namespace qrw
{
	Player::Player()
	:	name("Player")
	{
	}

	Player::~Player()
	{
		army.deleteAllUnits();
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

	bool Player::isActive() const
	{
		return active;
	}

	void Player::setActive(bool active)
	{
		active = active;
	}

	Army& Player::getArmy()
	{
		return army;
	}
}
