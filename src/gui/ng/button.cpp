#include <stdio.h>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "gui/ng/button.hpp"

namespace namelessgui
{

	Button::Button()
	: RectangularWidget(),
	  _label(new Label()),
	  _image(new RectangularWidget()),
	  _state(EWS_INACTIVE),
	  _defaultfont(new sf::Font())
	{
		// Add sub widgets
		this->addWidget(this->_label);
		this->addWidget(this->_image);

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

	void Button::setPosition(const sf::Vector2f& position)
	{
		RectangularWidget::setPosition(position);
		_image->setPosition(position);

		// Positioning with image
		if(_image->getTexture() != NULL)
		{
			_label->setPosition(sf::Vector2f(position.x + _image->getSize().x, position.y));
		}
		// Positioning without image
		else
		{
			_label->setAnchor({0.5f, 1.0f});
			_label->setParentAnchor({0.5f, 0.5f});
			_label->setRelativePosition({0.0f, 0.0f});
		}
	}

	void Button::setTextures(const sf::Texture* textureinactive,
		const sf::Texture* textureactive, const sf::Texture* texturehover)
	{
		_textures[EWS_INACTIVE] = textureinactive;
		_textures[EWS_ACTIVE] = textureactive;
		_textures[EWS_HOVER] = texturehover;
		updateSprite();
	}

	void Button::updateSprite()
	{
		if(_textures[_state] != nullptr)
			_image->setTexture(_textures[_state], true);
	}

	void Button::render(sf::RenderTarget& target, sf::RenderStates states) const
    {
		target.draw(static_cast<sf::RectangleShape>(*this));
		_label->render(target, states);
		_image->render(target, states);
    }

	void Button::leftMousebuttonPressedSlot()
	{
		_state = EWS_ACTIVE;
		this->setFillColor(sf::Color(50, 50, 50, 255));
		updateSprite();
	}

	void Button::mouseEnteredSlot()
	{
		_state = EWS_HOVER;
		this->setFillColor(sf::Color(80, 80, 80, 255));
		updateSprite();
	}

	void Button::clickedSlot()
	{
		_state = EWS_HOVER;
		this->setFillColor(sf::Color(60, 60, 60, 255));
		updateSprite();
	}

	void Button::mouseLeftSlot()
	{
		_state = EWS_INACTIVE;
		this->setFillColor(sf::Color(60, 60, 60, 255));
		updateSprite();
	}

}
