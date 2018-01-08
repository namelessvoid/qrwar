#include "gui/ng/widget.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "eventsystem/event.hpp"
#include "eventsystem/inputevents.hpp"

namespace namelessgui
{
	Widget::Widget(std::string id)
		: _parent(nullptr),
		  _visible(true),
		  _id(id),
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

	bool Widget::isVisible() const
	{
		return _visible;
	}

	void Widget::render(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if(_visible)
		{
			for(auto iter = _children.begin(); iter != _children.end(); ++iter)
				(*iter)->render(target, states);
		}
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
