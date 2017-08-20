#include "game/states/mainmenustate.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/BlendMode.hpp>
#include <SFML/Window/Event.hpp>

#include "config/settings.hpp"
#include "gui/texturemanager.hpp"
#include "gui/ng/button.hpp"

#include "gui/scene.hpp"

namespace qrw
{

MainMenuState::MainMenuState(sf::RenderWindow* renderWindow)
	: GameState(renderWindow, EGameStateId::EGSID_MAIN_MENU_STATE),
	  _quitClicked(false),
	  _newGameClicked(false)
{
	Settings* settings = Settings::getInstance();

	// Set up background
	TextureManager* textureManager = TextureManager::getInstance();
	_background.setTexture(textureManager->getTexture("mainmenubackground"));
	_background.setSize(sf::Vector2f(settings->getResolutionX(), settings->getResolutionY()));

	// Create main menu window
	namelessgui::Window* mainWindow = new namelessgui::Window();
	_guiUptr->addWidget(mainWindow);

	mainWindow->setSize(sf::Vector2f(145, 204));
	mainWindow->setRelativePosition(sf::Vector2f(15, 15));

	namelessgui::Button* button;
	sf::Vector2f buttonSize(139, 50);

	button = new namelessgui::Button();
	button->signalclicked.connect(std::bind(&MainMenuState::newGameClicked, this));
	button->setText("New Match");
	button->setSize(buttonSize);
	button->setParentAnchor({0.5f, 0.01f});
	button->setAnchor({0.5f, 0.0f});
	button->setRelativePosition({0.0f, 0.0f});
	mainWindow->addWidget(button);

	button = new namelessgui::Button();
	button->setText("Settings");
	button->setSize(buttonSize);
	button->setParentAnchor({0.5f, 0.01f});
	button->setAnchor({0.5f, 0.0f});
	button->setRelativePosition({0.0f, 50.0f});
	mainWindow->addWidget(button);

	button = new namelessgui::Button();
	button->setText("About");
	button->setSize(buttonSize);
	button->setParentAnchor({0.5f, 0.01f});
	button->setAnchor({0.5f, 0.0f});
	button->setRelativePosition({0.0f, 100.0f});
	mainWindow->addWidget(button);

	button = new namelessgui::Button();
	button->signalclicked.connect(std::bind(&MainMenuState::quitClicked, this));
	button->setText("Quit");
	button->setSize(buttonSize);
	button->setParentAnchor({0.5f, 0.01f});
	button->setAnchor({0.5f, 0.0f});
	button->setRelativePosition({0.0f, 150.0f});
	mainWindow->addWidget(button);

	_guiUptr->setVisible(true);
}

void MainMenuState::init(GameState* previousState)
{
	// Initialization that is only necessary at startup
	if(previousState->getId() == EGameStateId::EGSID_INTRO_STATE)
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
	}

	GameState::init();
	g_scene.reset();

	_newGameClicked = false;
}

EGameStateId MainMenuState::update()
{
	if(_quitClicked)
		return EGSID_QUIT;
	if(_newGameClicked)
		return EGSID_MAP_EDITOR_STATE;
	return EGSID_NO_CHANGE;
}

void MainMenuState::draw()
{
	_renderWindow->draw(_background);
	_guiUptr->render(*_renderWindow, sf::RenderStates::Default);
}

void MainMenuState::quitClicked()
{
	_quitClicked = true;
}

void MainMenuState::newGameClicked()
{
	_newGameClicked = true;
}



} // namespace qrw

