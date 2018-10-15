#include "gui/ng/widget.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "eventsystem/event.hpp"
#include "eventsystem/inputevents.hpp"

namespace namelessgui
{
	Widget::Widget(std::string id)
		: parent_(nullptr),
		  visible_(true),
		  id_(id),
		  parentAnchor_(0, 0),
		  anchor_(0, 0),
		  relativePosition_(0, 0)
    {
    }

    Widget::~Widget()
    {
		for(auto widget : children_)
			delete widget;
	}

	const std::string& Widget::getId() const
	{
		return id_;
	}

	void Widget::setParent(const Widget* parent)
	{
		parent_ = parent;
		setRelativePosition(getPosition());
	}

	void Widget::addWidget(Widget* widget)
	{
		children_.push_back(widget);
		widget->setParent(this);
	}

void Widget::removeWidget(const Widget* widget)
{
	children_.remove(const_cast<Widget*>(widget));
}

	void Widget::setVisible(bool visible)
	{
		this->visible_ = visible;
		for(auto iter = children_.begin(); iter != children_.end(); ++iter)
		{
			(*iter)->setVisible(visible);
		}
	}

	bool Widget::isVisible() const
	{
		return visible_;
	}

	void Widget::render(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if(visible_)
		{
			for(auto iter = children_.begin(); iter != children_.end(); ++iter)
				(*iter)->render(target, states);
		}
	}

	bool Widget::handleEvent(const qrw::IEvent& event)
	{
		if(!isVisible())
			return false;

		for(auto iter = children_.rbegin(); iter != children_.rend(); ++iter)
		{
			if((*iter)->handleEvent(event))
				return true;
		}

		return false;
	}

	void Widget::setParentAnchor(const sf::Vector2f& anchor)
	{
		parentAnchor_ = anchor;
		updatePosition();
	}

	void Widget::setAnchor(const sf::Vector2f& anchor)
	{
		anchor_ = anchor;
		updatePosition();
	}

	void Widget::setRelativePosition(const sf::Vector2f& relativePosition)
	{
		relativePosition_ = relativePosition;
		updatePosition();
	}

	void Widget::updatePosition()
	{
		if(parent_ == nullptr)
		{
			setPosition(relativePosition_);
		}
		else
		{
			sf::Vector2f parentPosition = parent_->getPosition();
			sf::Vector2f parentSize = parent_->getSize();

			sf::Vector2f position = {
				parentPosition.x + parentAnchor_.x * parentSize.x - anchor_.x * getSize().x,
				parentPosition.y + parentAnchor_.y * parentSize.y - anchor_.y * getSize().y
			};

			setPosition(relativePosition_ + position);
		}

		for(auto child : children_)
			child->updatePosition();
	}
}
