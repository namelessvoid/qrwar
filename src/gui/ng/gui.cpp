#include "gui/ng/gui.hpp"

#include "SFML/Graphics/RenderWindow.hpp"

namespace namelessgui
{

Gui::Gui(sf::RenderWindow* renderWindow)
	: Widget(),
	  _renderWindow(renderWindow),
	  _size(renderWindow->getSize())
{
}

Gui::~Gui()
{
}

sf::FloatRect Gui::getGlobalBounds()
{
	return {getPosition().x, getPosition().y, getSize().x, getSize().y};
}

void Gui::setSize(const sf::Vector2f&)
{
	// Ignored
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
