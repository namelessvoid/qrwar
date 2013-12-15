#include "gui/ng/label.hpp"

namespace namelessgui
{
	Label::Label(sf::Window* window, float width, float height)
		:	Widget(window, width, height),
			text()
	{}

	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(text);
	}

	sf::FloatRect Label::getGlobalBounds()
	{
		return text.getGlobalBounds();
	}

	void Label::setFont(sf::Font& font)
	{
		text.setFont(font);
	}

	void Label::setColor(const sf::Color& color)
	{
		text.setColor(color);
	}

	void Label::setCharacterSize(unsigned int size)
	{
		text.setCharacterSize(size);
	}

	void Label::setText(const sf::String& text)
	{
		this->text.setString(text);
	}

	void Label::setPosition(float x, float y)
	{
		text.setPosition(x, y);
	}
}