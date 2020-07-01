//
// Created by pommes on 13.04.20.
//

#ifndef QUADRULEDWAR_UNITMOCK_HPP
#define QUADRULEDWAR_UNITMOCK_HPP

#include "game/skirmish/unit.hpp"

class UnitMock : public qrw::Unit
{
public:
	UnitMock() : Unit() {
		setMaxMovement(10);
		setCurrentMovement(10);
	};

	void setWorldPosition(const sf::Vector2f& position) override { setWorldPositionCalls.push_back(position); }
	std::vector<sf::Vector2f> setWorldPositionCalls;

	void setPlayer(qrw::Player::Ptr& player) override { Unit::setPlayer(player); }
};

#endif //QUADRULEDWAR_UNITMOCK_HPP
