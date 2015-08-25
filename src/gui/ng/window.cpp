#include "gui/ng/window.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>

namespace namelessgui
{
	Window::Window()
	 :	RectangleShape()
	{
		setFillColor(sf::Color(40, 40, 40, 255));
		setOutlineThickness(1);
		setOutlineColor(sf::Color(120, 120, 120));
	}

	Window::~Window()
	{
        for(auto widget : _children)
            delete widget;
	}

	void Window::setVisible(bool visible)
	{
		this->_visible = visible;
		for(std::vector<Widget*>::iterator iter = _children.begin(); iter != _children.end(); ++iter)
		{
			(*iter)->setVisible(visible);
		}
	}

	bool Window::isVisible() const
	{
		return _visible;
	}

	void Window::addWidget(Widget* widget)
	{
		_children.push_back(widget);
	}

	void Window::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if(_visible)
		{
			target.draw((sf::RectangleShape)*this);
			for(auto iter = _children.begin(); iter != _children.end(); ++iter)
				target.draw(*(*iter), states);
		}
	}

	void Window::handleEvent(const sf::Event& event)
	{
		if(_visible)
		{
			for(auto iter = _children.begin(); iter != _children.end(); ++iter)
				(*iter)->handleEvent(event);
		}
	}
}
