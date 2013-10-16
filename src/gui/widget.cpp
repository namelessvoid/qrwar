#include "gui/widget.hpp"

#include <SFML/Window/Mouse.hpp>

#include <iostream>

namespace qrw
{
    Widget::Widget(sf::Window* window)
        : mouseFocus(false),
          leftMouseButtonPressRegistered(false)
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

    void Widget::handleEvent(const sf::Event& event)
    {
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
}
