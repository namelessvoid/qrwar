#include "gui/ng/widget.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>
#include <stdio.h>

namespace namelessgui
{
	Widget::Widget(sf::RenderWindow* window, float width, float height)
		: _window(window),
		  _visible(true),
		  _leftMouseButtonPressRegistered(false),
		  _rightMouseButtonPressRegistered(false),
		  _mouseFocus(false)
    {
        // Set size
        _size.x = width;
        _size.y = height;
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
        bounds.width = _size.x;
        bounds.height = _size.y;

		sf::Vector2f mousepos;
		mousepos.x = (float)sf::Mouse::getPosition(*_window).x;
		mousepos.y = (float)sf::Mouse::getPosition(*_window).y;

		return bounds.contains(mousepos);
	}

    void Widget::setVisible(bool visibility)
    {
        _visible = visibility;
    }

    void Widget::handleEvent(const sf::Event& event)
    {
        // A widget that is not visible cannot handle any event
        if(!_visible)
            return;

        // printf("widget dim: x=%f / y=%f; w=%f / h=%f\n", getGlobalBounds().left, getGlobalBounds().top, size.x, size.y);

        // Handle mouse move evets
        if(event.type == sf::Event::MouseMoved)
        {
            if(!hasMouseFocus())
            {
                // Mouse focus lost
                if(_mouseFocus)
                {
                    _mouseFocus = false;
                    signalmouseleft.emit();
                    _leftMouseButtonPressRegistered = false;
                }
                return;
            } // if(!hasMouseFocus)
            else
            {
                // Got mouse focus
                if(!_mouseFocus)
                {
                    _mouseFocus = true;
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
            if(_mouseFocus)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    signalleftmousebuttonpressed.emit();
                    _leftMouseButtonPressRegistered = true;
                    return;
                }
                else if(event.mouseButton.button == sf::Mouse::Right)
                {
                    _rightMouseButtonPressRegistered = true;
                    return;
                }
            }
        } // else if(MouseButtonPressed)
        else if(event.type == sf::Event::MouseButtonReleased)
        {
            if(_mouseFocus)
            {
                if(event.mouseButton.button == sf::Mouse::Left
                    && _leftMouseButtonPressRegistered)
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
		this->_size = size;
	}

	sf::Vector2f Widget::getSize() const
	{
		return _size;
	}
}
