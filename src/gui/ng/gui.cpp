#include "gui/ng/gui.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "game/eventhandlerpriority.hpp"

namespace namelessgui
{

Gui::Gui(sf::RenderWindow* renderWindow)
	: Widget(),
	  EventHandler(qrw::EventHandlerPriority::HIGH),
	  _renderWindow(renderWindow),
	  _size(renderWindow->getSize())
{
}

Gui::~Gui()
{
}

void Gui::setSize(const sf::Vector2f& size)
{
	_size = size;
	updatePosition();
}

sf::Vector2f Gui::getSize() const
{
	return _size;
}

void Gui::setPosition(const sf::Vector2f&)
{
	// Ignored
}

sf::Vector2f Gui::getPosition() const
{
	return {0.0f, 0.0f};
}

} // namespace namelessgui
