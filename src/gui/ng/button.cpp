#include <stdio.h>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "gui/ng/colors.hpp"
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
		this->signalLeftMouseButtonPressed.connect(std::bind(&Button::leftMousebuttonPressedSlot, this));
		this->signalMouseFocusGained.connect(std::bind(&Button::mouseEnteredSlot, this));
		this->signalClicked.connect(std::bind(&Button::clickedSlot, this));
		this->signalMouseFocusLost.connect(std::bind(&Button::mouseLeftSlot, this));

		this->setFillColor(BUTTON_DEFAULT_FILL_COLOR);
		this->setOutlineColor(BUTTON_OUTLINE_COLOR);
		this->setOutlineThickness(2.0f);
		this->setSize({100.0f, 30.0f});
	}

	Button::~Button()
	{}

	void Button::setText(std::string text)
	{
		_label->setText(text);
		if(_label->getTextSize().x > getSize().x)
			setSize({_label->getTextSize().x + 10.0f, getSize().y});
		updatePosition();
	}

	const std::string& Button::getText() const
	{
		return _label->getText();
	}

	void Button::setFontSize(unsigned int fontSize)
	{
		_label->setFontSize(fontSize);
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
		this->setFillColor(BUTTON_ACTIVE_FILL_COLOR);
	}

	void Button::mouseEnteredSlot()
	{
		this->setFillColor(BUTTON_HOVER_FILL_COLOR);
	}

	void Button::clickedSlot()
	{
		if(!hasMouseFocus())
			this->setFillColor(BUTTON_DEFAULT_FILL_COLOR);
		else
			this->setFillColor(BUTTON_HOVER_FILL_COLOR);
	}

	void Button::mouseLeftSlot()
	{
		this->setFillColor(sf::Color(60, 60, 60, 255));
	}

}
