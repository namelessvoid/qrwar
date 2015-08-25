#include "gamestates/mainmenustate.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/BlendMode.hpp>

#include "config/settings.hpp"
#include "gui/texturemanager.hpp"

namespace qrw
{

MainMenuState::MainMenuState(sf::RenderWindow* renderWindow)
	: GameState(renderWindow, EGameStateId::EGSID_MAIN_MENU_STATE)
{

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
}

void MainMenuState::handleEvent(sf::Event& event)
{

}

} // namespace qrw

