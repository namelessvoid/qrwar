#include <stdio.h>

#include "engine/player.hpp"

namespace qrw
{
	Player::Player()
	:	_name("Player")
	{
	}

	Player::~Player()
	{
	}

	std::string Player::getName()
	{
		return _name;
	}

	void Player::setName(std::string name)
	{
		this->_name = name;
	}

	int Player::getId()
	{
		return _id;
	}

	void Player::setId(int id)
	{
		this->_id = id;
	}

	bool Player::isActive() const
	{
		return _active;
	}

	void Player::setActive(bool active)
	{
		this->_active = active;
	}
}
