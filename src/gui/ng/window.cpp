#include "gui/ng/window.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>

namespace namelessgui
{
	Window::Window()
	 :	RectangularWidget()
	{
		setFillColor(sf::Color(40, 40, 40, 255));
		setOutlineThickness(1);
		setOutlineColor(sf::Color(120, 120, 120));
		setSize({100.0f, 120.0f});
	}

	Window::~Window()
	{
	}
}
