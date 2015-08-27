#include "gui/ng/label.hpp"

namespace namelessgui
{
	Label::Label()
		:	Widget(),
			_text()
	{}

	void Label::render(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(_text);
	}

	sf::FloatRect Label::getGlobalBounds()
	{
		return _text.getGlobalBounds();
	}

	void Label::setFont(sf::Font& font)
	{
		_text.setFont(font);
	}

	void Label::setColor(const sf::Color& color)
	{
		_text.setColor(color);
	}

	void Label::setCharacterSize(unsigned int size)
	{
		_text.setCharacterSize(size);
	}

	void Label::setText(const sf::String& text)
	{
		this->_text.setString(text);
	}

	void Label::setPosition(float x, float y)
	{
		_text.setPosition(x, y);
	}
}
