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

	sf::Vector2f Label::getPosition() const
	{
		return this->_text.getPosition();
	}

	sf::Vector2f Label::getSize() const
	{
		return sf::Vector2f(this->_text.getGlobalBounds().width, this->_text.getGlobalBounds().height);
	}

	void Label::setPosition(const sf::Vector2f& position)
	{
		_text.setPosition(position);
	}
}
