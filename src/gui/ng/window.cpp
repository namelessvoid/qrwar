#include "gui/ng/window.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "eventsystem/inputevents.hpp"

#include "core/mouse.hpp"

#include "gui/ng/colors.hpp"

namespace namelessgui
{

Window::Window(const std::string& id)
	:	RectangularWidget(id)
{
	setFillColor(DEFAULT_FILL_COLOR);
	setOutlineThickness(1);
	setOutlineColor(DEFAULT_OUTLINE_COLOR);
	setSize({100.0f, 120.0f});
}

Window::~Window()
{
}

bool Window::handleEvent(const qrw::IEvent& event)
{
	if(Widget::handleEvent(event))
		return true;
	
	const qrw::SID eventName = event.getName();
	if(eventName == qrw::LeftMouseButtonPressedEvent::name
	   || eventName == qrw::RightMouseButtonPressedEvent::name)
	{
		sf::Vector2i mousePosition = qrw::Mouse::getPosition();
		if(getWidgetArea().contains({(float)mousePosition.x, (float)mousePosition.y}))
			return true;
	}

	return false;
}

} // namespace qrw
