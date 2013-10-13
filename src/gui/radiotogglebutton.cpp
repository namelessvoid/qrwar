#include <SFML/Graphics/RectangleShape.hpp>

#include "gui/radiotogglebutton.hpp"

namespace qrw
{
	RadioToggleButton::RadioToggleButton(sf::Window* window,
		ButtonGroup* buttongroup, std::string text, const sf::Texture* textureactive,
		const sf::Texture* textureinainactive,
		const sf::Texture* texturehover)
	: Button(window, text, textureactive, textureinainactive, texturehover),
	  buttongroup(buttongroup)
	{
		this->buttongroup->addButton(this);
	}

	RadioToggleButton::~RadioToggleButton()
	{
	}

	void RadioToggleButton::handleEvent(const sf::Event& event)
	{
		if(hasMouseFocus() == false)
			return;

		if(event.type == sf::Event::MouseButtonPressed
			&& event.mouseButton.button == sf::Mouse::Left)
		{
			buttongroup->activateButton(this);
		}
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
