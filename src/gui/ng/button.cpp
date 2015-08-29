#include <stdio.h>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "gui/ng/button.hpp"

namespace namelessgui
{

	Button::Button()
	: RectangularWidget(),
	  _label(new Label()),
	  _image(nullptr),
	  _state(EWS_INACTIVE)
	{
		// Add sub widgets
		this->addWidget(this->_label);

		// Connect signals to slots
		this->signalleftmousebuttonpressed.connect(std::bind(&Button::leftMousebuttonPressedSlot, this));
		this->signalmouseentered.connect(std::bind(&Button::mouseEnteredSlot, this));
		this->signalclicked.connect(std::bind(&Button::clickedSlot, this));
		this->signalmouseleft.connect(std::bind(&Button::mouseLeftSlot, this));

		this->setFillColor(sf::Color(60, 60, 60, 255));
		this->setOutlineColor(sf::Color(30, 30, 30, 255));
		this->setOutlineThickness(2.0f);
		this->setSize({100.0f, 30.0f});
	}

	Button::~Button()
	{}

	void Button::setText(std::string text)
	{
		this->_label->setText(text);
	}

	void Button::setImage(const sf::Texture* texture)
	{
		if(!_image)
		{
			_image  = new RectangularWidget();
			_image->setSize({getSize().y, getSize().y});
			_image->setFillColor({255, 255, 255, 255});
			addWidget(_image);
		}
		_image->setTexture(texture);
		_image->setVisible(true);
	}

	void Button::setPosition(const sf::Vector2f& position)
	{
		RectangularWidget::setPosition(position);

		// Positioning with image
		if(_image != nullptr)
		{
			_image->setPosition(position);
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

	void Button::setSize(const sf::Vector2f& size)
	{
		RectangleShape::setSize(size);

		if(_image != nullptr)
			_image->setSize({size.y, size.y});
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
		if(!_visible)
			return;

		target.draw(static_cast<sf::RectangleShape>(*this));
		Widget::render(target, states);
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
		if(!hasMouseFocues())
			this->setFillColor(sf::Color(60, 60, 60, 255));
		else
			this->setFillColor(sf::Color(80, 80, 80, 255));
		updateSprite();
	}

	void Button::mouseLeftSlot()
	{
		_state = EWS_INACTIVE;
		this->setFillColor(sf::Color(60, 60, 60, 255));
		updateSprite();
	}

}
