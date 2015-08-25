#include "gamestates/mainmenustate.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/BlendMode.hpp>
#include <SFML/Window/Event.hpp>

#include "config/settings.hpp"
#include "gui/texturemanager.hpp"

#include <iostream>

namespace qrw
{

MainMenuState::MainMenuState(sf::RenderWindow* renderWindow)
	: GameState(renderWindow, EGameStateId::EGSID_MAIN_MENU_STATE)
{
	_mainWindow.setFillColor(sf::Color(0, 255, 0, 0));
	_mainWindow.setSize(sf::Vector2f(100, 100));
}

void MainMenuState::init(GameState* previousState)
{
	Settings* settings = Settings::getInstance();

	sf::Uint32 style = sf::Style::Default;

	if(settings->getFullscreen())
		style = sf::Style::Fullscreen;

	_renderWindow->create(
		sf::VideoMode(settings->getResolutionX(), settings->getResolutionY()),
		"QRW",
		style
	);

	// Set up textures
	TextureManager* textureManager = TextureManager::getInstance();

	// Set background texture
	_background.setSize(sf::Vector2f(settings->getResolutionX(), settings->getResolutionY()));
	_background.setTexture(textureManager->getTexture("mainmenubackground"));
}

EGameStateId MainMenuState::update()
{
	return EGameStateId::EGSID_NO_CHANGE;
}

void MainMenuState::draw()
{
	_renderWindow->draw(_background);
	_renderWindow->draw(_mainWindow);
}

void MainMenuState::handleEvent(sf::Event& event)
{
	if(event.type == sf::Event::Resized)
		_renderWindow->setView(sf::View(sf::FloatRect(0.0f, 0.0f, event.size.width, event.size.height)));
}

} // namespace qrw

