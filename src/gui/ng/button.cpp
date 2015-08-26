#include <stdio.h>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "gui/ng/button.hpp"

namespace namelessgui
{

	Button::Button(sf::RenderWindow* window, float width, float height, std::string text,
		const sf::Texture* textureactive,
		const sf::Texture* textureinactive,
		const sf::Texture* texturehover)
	: RectangularWidget(window, width, height),
	  _label(new Label(window)),
	  _image(new RectangularWidget(window, 48, 48)),
	  _state(ES_INACTIVE),
	  _defaultfont(new sf::Font())
	{
		_defaultfont->loadFromFile("./res/font/Knigqst.ttf");
		this->_label->setFont(*_defaultfont);
		this->_label->setCharacterSize(25);
		this->_label->setText(text);

		if(textureactive != NULL && textureinactive != NULL && texturehover != NULL)
			setTextures(textureactive, textureinactive, texturehover);

		for(int i = 0; i < 3; ++i)
			_textures[i] = 0;

		// Connect signals to slots
		this->signalleftmousebuttonpressed.connect(std::bind(&Button::leftMousebuttonPressedSlot, this));
		this->signalmouseentered.connect(std::bind(&Button::mouseEnteredSlot, this));
		this->signalclicked.connect(std::bind(&Button::clickedSlot, this));
		this->signalmouseleft.connect(std::bind(&Button::mouseLeftSlot, this));

		this->setFillColor(sf::Color(60, 60, 60, 255));
		this->setOutlineColor(sf::Color(30, 30, 30, 255));
		this->setOutlineThickness(2.0f);
	}

	Button::~Button()
	{}

	void Button::setText(std::string text)
	{
		this->_label->setText(text);
	}

	void Button::setState(Button::STATES state)
	{
		this->_state = state;
	}

	Button::STATES Button::getState() const
	{
		return _state;
	}

	void Button::setPosition(float x, float y)
	{
		RectangularWidget::setPosition(x, y);
		_image->setPosition(x, y);
		if(_image->getTexture() != NULL)
		{
			_label->setPosition(x + _image->getSize().x, y);
		}
		else
		{
			_label->setPosition(x, y);
		}
	}

	void Button::setPosition(const sf::Vector2f& position)
	{
		setPosition(position.x, position.y);

	}

	void Button::setTextures(const sf::Texture* textureinactive,
		const sf::Texture* textureactive, const sf::Texture* texturehover)
	{
		_textures[ES_INACTIVE] = textureinactive;
		_textures[ES_ACTIVE] = textureactive;
		_textures[ES_HOVER] = texturehover;
		updateSprite();
	}

	void Button::updateSprite()
	{
		if(_textures[_state] != 0)
		{
			_image->setTexture(_textures[_state], true);
			setPosition(getPosition());
		}
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
		target.draw(static_cast<sf::RectangleShape>(*this));
		target.draw(*_label);
		target.draw(static_cast<sf::RectangleShape>(*_image));
    }

	void Button::leftMousebuttonPressedSlot()
	{
		_state = ES_ACTIVE;
		this->setFillColor(sf::Color(50, 50, 50, 255));
		updateSprite();
	}

	void Button::mouseEnteredSlot()
	{
		_state = ES_HOVER;
		this->setFillColor(sf::Color(80, 80, 80, 255));
		updateSprite();
	}

	void Button::clickedSlot()
	{
		_state = ES_HOVER;
		this->setFillColor(sf::Color(60, 60, 60, 255));
		updateSprite();
	}

	void Button::mouseLeftSlot()
	{
		_state = ES_INACTIVE;
		this->setFillColor(sf::Color(60, 60, 60, 255));
		updateSprite();
	}

}
