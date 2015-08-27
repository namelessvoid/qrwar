#include "gui/ng/widget.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>
#include <stdio.h>

namespace namelessgui
{
	Widget::Widget(const Widget* parent)
		: _parent(parent),
		  _visible(true),
		  _leftMouseButtonPressRegistered(false),
		  _rightMouseButtonPressRegistered(false),
		  _mouseFocus(false)
    {
    }

    Widget::~Widget()
    {
		for(auto widget : _children)
			delete widget;
    }

	void Widget::addWidget(Widget* widget)
	{
		_children.push_back(widget);
	}

	void Widget::setVisible(bool visible)
	{
		this->_visible = visible;
		for(std::vector<Widget*>::iterator iter = _children.begin(); iter != _children.end(); ++iter)
		{
			(*iter)->setVisible(visible);
		}
	}

	void Widget::render(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if(_visible)
		{
			for(auto iter = _children.begin(); iter != _children.end(); ++iter)
				(*iter)->render(target, states);
		}
	}

    void Widget::handleEvent(const sf::Event& event)
    {
        // A widget that is not visible cannot handle any event
        if(!_visible)
            return;

		// Let sub widgets also handle the event
		for(auto iter = _children.begin(); iter != _children.end(); ++iter)
			(*iter)->handleEvent(event);

        // Handle mouse move evets
        if(event.type == sf::Event::MouseMoved)
        {
			if(!getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
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
}
