#include "gui/widget.hpp"

#include <SFML/Window/Mouse.hpp>

#include <iostream>
#include <stdio.h>

namespace qrw
{
    Widget::Widget(sf::Window* window, float width, float height)
        : mouseFocus(false),
          visible(true),
          leftMouseButtonPressRegistered(false)
    {
        this->window = window;

        // Set size
        size.x = width;
        size.y = height;
    }

    Widget::Widget(sf::Window* window, sf::Vector2f size)
    {
        Widget(window, size.x, size.y);
    }

    Widget::~Widget()
    {
    }

    bool Widget::hasMouseFocus()
	{
		sf::FloatRect bounds = getGlobalBounds();
        bounds.width = size.x;
        bounds.height = size.y;

		sf::Vector2f mousepos;
		mousepos.x = (float)sf::Mouse::getPosition(*window).x;
		mousepos.y = (float)sf::Mouse::getPosition(*window).y;

		return bounds.contains(mousepos);
	}

    void Widget::setVisible(bool visibility)
    {
        visible = visibility;
    }

    void Widget::handleEvent(const sf::Event& event)
    {
        // A widget that is not visible cannot handle any event
        if(!visible)
            return;

        // printf("widget dim: x=%f / y=%f; w=%f / h=%f\n", getGlobalBounds().left, getGlobalBounds().top, size.x, size.y);

        // Handle mouse move evets
        if(event.type == sf::Event::MouseMoved)
        {
            if(!hasMouseFocus())
            {
                // Mouse focus lost
                if(mouseFocus)
                {
                    mouseFocus = false;
                    signalmouseleft.emit();
                    leftMouseButtonPressRegistered = false;
                    std::cout << "Mouse left widget.\n";
                }
                return;
            } // if(!hasMouseFocus)
            else
            {
                // Got mouse focus
                if(!mouseFocus)
                {
                    mouseFocus = true;
                    signalmouseentered.emit();
                    std::cout << "mouse entered widget.\n";
                }
                // just moved when already has mouse focus
                else
                {
                    signalmousemoved.emit();
                    std::cout << "mouse moved in widget.\n";
                }
                return;
            } // else(hasMouseFocus)
        } // if(MouseMoveEvent)
        else if(event.type == sf::Event::MouseButtonPressed)
        {
            if(mouseFocus)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    signalleftmousebuttonpressed.emit();
                    leftMouseButtonPressRegistered = true;
                    std::cout << "Mouse button on widget pressed.\n";
                    return;
                }
            }
        }
        else if(event.type == sf::Event::MouseButtonReleased)
        {
            if(mouseFocus)
            {
                if(event.mouseButton.button == sf::Mouse::Left
                    && leftMouseButtonPressRegistered)
                {
                    signalclicked.emit();
                    std::cout << "Widget was clicked.\n";
                    return;
                }
            }
        } // else(MouseButtonEvent)
    }

    void Widget::disconnectAllSignals()
    {
        this->signalclicked.disconnectAll();
        this->signalleftmousebuttonpressed.disconnectAll();
        this->signalmouseleft.disconnectAll();
        this->signalmouseentered.disconnectAll();
    }

    void Widget::setSize(sf::Vector2f size)
    {
        this->size = size;
    }

    sf::Vector2f Widget::getSize() const
    {
        return size;
    }
}
