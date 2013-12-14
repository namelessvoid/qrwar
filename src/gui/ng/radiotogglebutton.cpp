#include <SFML/Graphics/RectangleShape.hpp>

#include "gui/ng/radiotogglebutton.hpp"

namespace namelessgui
{
	RadioToggleButton::RadioToggleButton(sf::Window* window, ButtonGroup* buttongroup,
		float width, float height,
		std::string text, const sf::Texture* textureactive,
		const sf::Texture* textureinainactive,
		const sf::Texture* texturehover)
	: Button(window, width, height, text, textureactive, textureinainactive, texturehover),
	  buttongroup(buttongroup)
	{
		buttongroup->addButton(this);
		disconnectAllSignals();
		signalclicked.connect(std::bind(&RadioToggleButton::clickedSlot, this));
	}

	RadioToggleButton::~RadioToggleButton()
	{
	}

	void RadioToggleButton::clickedSlot()
	{
		buttongroup->activateButton(this);
		updateSprite();
	}

	void RadioToggleButton::draw(sf::RenderTarget& target,
		sf::RenderStates states) const
	{
		if(getState() == ES_ACTIVE)
		{
			sf::RectangleShape rect;
			rect.setFillColor(sf::Color::Red);
			rect.setPosition(getPosition().x, getPosition().y);
			rect.setSize(getSize());
			target.draw(rect);
		}
		target.draw(*text);
		target.draw((sf::Sprite)*this);
	}
}
