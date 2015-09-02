#include "gamestates/gamestate.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "config/settings.hpp"

namespace qrw
{

GameState::GameState(sf::RenderWindow* renderWindow, EGameStateId id)
	: _renderWindow(renderWindow),
	  _guiUptr(new namelessgui::Gui(renderWindow)),
	  _id(id)
{
	Settings* settings = Settings::getInstance();

	_guiUptr->setSize(sf::Vector2f(settings->getResolutionX(), settings->getResolutionY()));
}

GameState::~GameState()
{
}

void GameState::handleEvent(sf::Event& event)
{
	if(event.type == sf::Event::Resized)
		_renderWindow->setView(sf::View(sf::FloatRect(0.0f, 0.0f, event.size.width, event.size.height)));
}

EGameStateId GameState::getId()
{
	return _id;
}

} // namespace qrw
