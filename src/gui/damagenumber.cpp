#include "gui/damagenumber.hpp"

#include "tostring.hpp"

namespace qrw
{
	DamageNumber::DamageNumber(int damagedone, sf::Vector2f postition)
		// Animation(duration, loop, deleteonstop)
		: Animation(1.0f, false, true)
	{
		font.loadFromFile("./res/font/Knigqst.ttf");
		text.setFont(font);
		text.setCharacterSize(20);
		text.setString("-" + intToString(damagedone) + " HP");
		text.setPosition(postition);
		text.setColor(sf::Color::Red);
	}

	DamageNumber::~DamageNumber()
	{
	}

	void DamageNumber::update(sf::Time elapsedtime)
	{
		Animation::update(elapsedtime);
	}

	void DamageNumber::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(text, states);
	}
}