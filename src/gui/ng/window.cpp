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
	}

	void Window::setVisible(bool visible)
	{
		this->visible = visible;
		for(std::vector<Widget*>::iterator iter = children.begin(); iter != children.end(); ++iter)
		{
			(*iter)->setVisible(visible);
		}
	}

	bool Window::isVisible() const
	{
		return visible;
	}

	void Window::addWidget(Widget* widget)
	{
		children.push_back(widget);
	}

	void Window::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if(visible)
		{
			target.draw((sf::RectangleShape)*this);
			for(auto iter = children.begin(); iter != children.end(); ++iter)
				target.draw(*(*iter), states);
		}
	}

	void Window::handleEvent(const sf::Event& event)
	{
		if(visible)
		{
			for(auto iter = children.begin(); iter != children.end(); ++iter)
				(*iter)->handleEvent(event);
		}
	}
}
