#include "gui/window.hpp"

namespace qrw
{
	Window::Window()
	{
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

	void Window::addWidget(Widget* widget)
	{
		children.push_back(widget);
	}
}