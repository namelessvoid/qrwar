#include "gui/ng/widget.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>
#include <stdio.h>

namespace namelessgui
{
	Widget::Widget(sf::RenderWindow* window, float width, float height)
        : mouseFocus(false),
          visible(true),
          leftMouseButtonPressRegistered(false),
          rightMouseButtonPressRegistered(false)
    {
        this->window = window;

        // Set size
        size.x = width;
        size.y = height;
    }

	Widget::Widget(sf::RenderWindow* window, sf::Vector2f size)
        : Widget(window, size.x, size.y)
    {
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
                }
                // just moved when already has mouse focus
                else
                {
                    signalmousemoved.emit();
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
                    return;
                }
                else if(event.mouseButton.button == sf::Mouse::Right)
                {
                    rightMouseButtonPressRegistered = true;
                    return;
                }
            }
        } // else if(MouseButtonPressed)
        else if(event.type == sf::Event::MouseButtonReleased)
        {
            if(mouseFocus)
            {
                if(event.mouseButton.button == sf::Mouse::Left
                    && leftMouseButtonPressRegistered)
                {
                    signalclicked.emit();
                    return;
                }
                else if(event.mouseButton.button == sf::Mouse::Right)
                {
                    signalrightclicked.emit();
                    return;
                }

            }
        } // else(MouseButtonReleased)
        else if(event.type == sf::Event::KeyPressed)
        {
            // TODO: check for keyboard focus.
            signalkeypressed.emit(event);
        }
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
