#include <stdio.h>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "gui/ng/button.hpp"
#include "gui/ng/label.hpp"

namespace namelessgui
{

	Button::Button(std::string id)
	: RectangularWidget(id),
      _label(new Label())
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

	const std::string& Button::getText() const
	{
		return _label->getText();
	}

	void Button::setImage(const sf::Texture* texture)
    {
        _label->setImage(texture);
	}

	void Button::setPosition(const sf::Vector2f& position)
	{
		RectangularWidget::setPosition(position);
        _label->setPosition(position);
	}

	void Button::setSize(const sf::Vector2f& size)
	{
		RectangleShape::setSize(size);
        _label->setSize(size);
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
		this->setFillColor(sf::Color(50, 50, 50, 255));
	}

	void Button::mouseEnteredSlot()
	{
		this->setFillColor(sf::Color(80, 80, 80, 255));
	}

	void Button::clickedSlot()
	{
		if(!hasMouseFocus())
			this->setFillColor(sf::Color(60, 60, 60, 255));
		else
			this->setFillColor(sf::Color(80, 80, 80, 255));
	}

	void Button::mouseLeftSlot()
	{
		this->setFillColor(sf::Color(60, 60, 60, 255));
	}

}
