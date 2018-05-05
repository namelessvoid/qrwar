#ifndef NAMELESSGUI_WINDOW_HPP
#define NAMELESSGUI_WINDOW_HPP value

#include <SFML/Graphics/RenderWindow.hpp>

#include "gui/ng/spritewidget.hpp"

namespace namelessgui
{
class Window : public RectangularWidget
{
public:
	Window(const std::string& id = "");
	~Window();

	bool handleEvent(const qrw::IEvent& event) override;
};
}
#endif
