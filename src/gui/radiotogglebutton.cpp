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
		if(mouseOnButton() == false)
			return;

		if(event.type == sf::Event::MouseButtonPressed
			&& event.mouseButton.button == sf::Mouse::Left)
		{
			buttongroup->activateButton(this);
			printf("activated button: status now %i\n", getState());
		}
	}

	void RadioToggleButton::renderTo(sf::RenderTarget& target,
		sf::RenderStates states) const
	{
		if(getState() == ES_ACTIVE)
		{
			sf::RectangleShape rect;
			rect.setFillColor(sf::Color::Red);
			rect.setPosition(getPosition().x, getPosition().y);
			rect.setSize(sf::Vector2f(32, 32));
			target.draw(rect);
		}
		target.draw(*this);
	}
}