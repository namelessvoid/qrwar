#include "gui/ng/widget.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "eventsystem/event.hpp"
#include "eventsystem/inputevents.hpp"

namespace namelessgui
{
	Widget::Widget(std::string id)
		: _parent(nullptr),
		  _visible(false),
		  _id(id),
		  _leftMouseButtonPressRegistered(false),
		  _rightMouseButtonPressRegistered(false),
		  _mouseFocus(false),
		  _parentAnchor(0, 0),
		  _anchor(0, 0),
		  _relativePosition(0, 0)
    {
    }

    Widget::~Widget()
    {
		for(auto widget : _children)
			delete widget;
	}

	const std::string& Widget::getId() const
	{
		return _id;
	}

	void Widget::setParent(const Widget* parent)
	{
		_parent = parent;
		setRelativePosition(getPosition());
	}

	void Widget::addWidget(Widget* widget)
	{
		_children.push_back(widget);
		widget->setVisible(_visible);
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

	bool Widget::hasMouseFocues() const
	{
		return _mouseFocus;
	}

//	void Widget::setState(Widget::EWidgetStates state)
//	{
//		this->_state = state;
//	}

//	Widget::EWidgetStates Widget::getState() const
//	{
//		return _state;
//	}

	void Widget::render(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if(_visible)
		{
			for(auto iter = _children.begin(); iter != _children.end(); ++iter)
				(*iter)->render(target, states);
		}
	}

	bool Widget::handleEvent(const qrw::Event& event)
    {
		bool stopEventPropagation = false;
        // A widget that is not visible cannot handle any event
        if(!_visible)
			return stopEventPropagation;

		// Let sub widgets also handle the event
		for(auto iter = _children.begin(); iter != _children.end(); ++iter)
			stopEventPropagation |= (*iter)->handleEvent(event);

        // Handle mouse move evets
		if(event.name == qrw::SID("MOUSE_MOVED"))
        {
			const qrw::MouseMovedEvent& moveEvent = static_cast<const qrw::MouseMovedEvent&>(event);
			if(!getGlobalBounds().contains(moveEvent.screenCoordinates.x, moveEvent.screenCoordinates.y))
            {
                // Mouse focus lost
                if(_mouseFocus)
                {
                    _mouseFocus = false;
                    signalmouseleft.emit();
                    _leftMouseButtonPressRegistered = false;
                }
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
            } // else(hasMouseFocus)
        } // if(MouseMoveEvent)

		if(_mouseFocus)
		{
			if(event.name == qrw::SID("LEFT_MOUSE_BUTTON_PRESSED"))
			{
				signalleftmousebuttonpressed.emit();
				_leftMouseButtonPressRegistered = true;
				stopEventPropagation = true;
			}
			else if(event.name == qrw::SID("RIGHT_MOUSE_BUTTON_PRESSED"))
			{
				_rightMouseButtonPressRegistered = true;
				stopEventPropagation = true;
			}
			else if(event.name == qrw::SID("LEFT_MOUSE_BUTTON_RELEASED") && _leftMouseButtonPressRegistered)
			{
				signalclicked.emit();
				stopEventPropagation = true;
			}
			else if(event.name == qrw::SID("RIGHT_MOUSE_BUTTON_RELEASED") && _rightMouseButtonPressRegistered)
			{
				signalrightclicked.emit();
				stopEventPropagation = true;
			}
		}

//        else if(event.type == sf::Event::KeyPressed)
//        {
//            // TODO: check for keyboard focus.
//            signalkeypressed.emit(event);
//        }

		return stopEventPropagation;
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
		updatePosition();
	}

	void Widget::setAnchor(const sf::Vector2f& anchor)
	{
		_anchor = anchor;
		updatePosition();
	}

	void Widget::setRelativePosition(const sf::Vector2f& relativePosition)
	{
		_relativePosition = relativePosition;
		updatePosition();
	}

	void Widget::updatePosition()
	{
		if(_parent == nullptr)
		{
			setPosition(_relativePosition);
		}
		else
		{
			sf::Vector2f parentPosition = _parent->getPosition();
			sf::Vector2f parentSize = _parent->getSize();

			sf::Vector2f position = {
				parentPosition.x + _parentAnchor.x * parentSize.x - _anchor.x * getSize().x,
				parentPosition.y + _parentAnchor.y * parentSize.y - _anchor.y * getSize().y
			};

			setPosition(_relativePosition + position);
		}

		for(auto child : _children)
			child->updatePosition();
	}
}
