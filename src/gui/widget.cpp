#include "gui/widget.hpp"

#include <SFML/Window/Mouse.hpp>

namespace qrw
{
    Widget::Widget(sf::Window* window)
    {
        this->window = window;
    }

    Widget::~Widget()
    {
    }

    bool Widget::hasMouseFocus()
	{
		sf::FloatRect bounds = getGlobalBounds();

		sf::Vector2f mousepos;
		mousepos.x = (float)sf::Mouse::getPosition(*window).x;
		mousepos.y = (float)sf::Mouse::getPosition(*window).y;

		return bounds.contains(mousepos);
	}

    void Widget::handleEvent(sf::Event& event)
    {

    }
}
