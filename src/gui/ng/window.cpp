#include "gui/ng/window.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "gui/ng/colors.hpp"

namespace namelessgui
{
	Window::Window()
	 :	RectangularWidget()
	{
		setFillColor(DEFAULT_FILL_COLOR);
		setOutlineThickness(1);
		setOutlineColor(DEFAULT_OUTLINE_COLOR);
		setSize({100.0f, 120.0f});
	}

	Window::~Window()
	{
	}
}
