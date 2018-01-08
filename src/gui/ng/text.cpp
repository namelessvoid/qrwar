#include "gui/ng/text.hpp"

namespace namelessgui
{
	Text::Text()
		:	Widget(),
			_text()
	{
		_font.loadFromFile("./res/font/Knigqst.ttf");
		_text.setFont(_font);
		_text.setCharacterSize(25);
	}

	void Text::render(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(_text);
	}

	sf::FloatRect Text::getWidgetArea()
	{
		return _text.getGlobalBounds();
	}

	void Text::setFont(sf::Font& font)
	{
		_text.setFont(font);
	}

	void Text::setColor(const sf::Color& color)
	{
        _text.setFillColor(color);
	}

	void Text::setCharacterSize(unsigned int size)
	{
		_text.setCharacterSize(size);
	}

	void Text::setText(const std::string text)
	{
		_stdText = text;
		_text.setString(text);
		updatePosition();
	}

	const std::string& Text::getText() const
	{
		return _stdText;
	}

	sf::Vector2f Text::getPosition() const
	{
		return this->_text.getPosition();
	}

	sf::Vector2f Text::getSize() const
	{
		return sf::Vector2f(this->_text.getGlobalBounds().width, this->_text.getGlobalBounds().height);
	}

	void Text::setPosition(const sf::Vector2f& position)
	{
		_text.setPosition(position);
	}
}
