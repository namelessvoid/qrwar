#include "gui/ng/widget.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace namelessgui
{
	Widget::Widget()
		: _parent(nullptr),
		  _visible(false),
		  _state(EWS_INACTIVE),
		  _leftMouseButtonPressRegistered(false),
		  _rightMouseButtonPressRegistered(false),
		  _mouseFocus(false),
		  _parentAnchor(0, 0),
		  _anchor(0, 0)
    {
    }

    Widget::~Widget()
    {
		for(auto widget : _children)
			delete widget;
	}

	void Widget::setParent(const Widget* parent)
	{
		_parent = parent;
		setRelativePosition(getPosition());
	}

	void Widget::addWidget(Widget* widget)
	{
		_children.push_back(widget);
		widget->setParent(this);
	}

	void Widget::setVisible(bool visible)
	{
		this->_visible = visible;
		for(std::vector<Widget*>::iterator iter = _children.begin(); iter != _children.end(); ++iter)
		{
			(*iter)->setVisible(visible);
		}
	}

	bool Widget::isVisible()
	{
		return _visible;
	}

	void Widget::setState(Widget::EWidgetStates state)
	{
		this->_state = state;
	}

	Widget::EWidgetStates Widget::getState() const
	{
		return _state;
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

	void Widget::setParentAnchor(const sf::Vector2f& anchor)
	{
		_parentAnchor = anchor;
	}

	void Widget::setAnchor(const sf::Vector2f& anchor)
	{
		_anchor = anchor;
	}

	void Widget::setRelativePosition(const sf::Vector2f& relativePosition)
	{
		if(_parent == nullptr)
		{
			setPosition(relativePosition);
			return;
		}

		sf::Vector2f parentPosition = _parent->getPosition();
		sf::Vector2f parentSize = _parent->getSize();

		sf::Vector2f position = {
			parentPosition.x + _parentAnchor.x * parentSize.x - _anchor.x * getSize().x,
			parentPosition.y + _parentAnchor.y * parentSize.y - _anchor.y * getSize().y
		};

		setPosition(relativePosition + position);
	}
}
