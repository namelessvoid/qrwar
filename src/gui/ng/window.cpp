#include "gui/ng/window.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>

namespace namelessgui
{
	Window::Window(sf::RenderWindow* renderWindow)
	 :	RectangularWidget(renderWindow)
	{
		setFillColor(sf::Color(40, 40, 40, 255));
		setOutlineThickness(1);
		setOutlineColor(sf::Color(120, 120, 120));
	}

	Window::~Window()
	{
	}
}
