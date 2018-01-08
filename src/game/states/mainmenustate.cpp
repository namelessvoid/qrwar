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
	  nextState_(EGSID_NO_CHANGE)
{
	Settings* settings = Settings::getInstance();

	// Set up background
	TextureManager* textureManager = TextureManager::getInstance();
	background_.setTexture(textureManager->getTexture("mainmenubackground"));
	background_.setSize(sf::Vector2f(settings->getResolutionX(), settings->getResolutionY()));

	// Create main menu window
	namelessgui::Window* mainWindow = new namelessgui::Window();
	_guiUptr->addWidget(mainWindow);

	mainWindow->setSize(sf::Vector2f(145, 254));
	mainWindow->setRelativePosition(sf::Vector2f(15, 15));

	namelessgui::Button* button;
	sf::Vector2f buttonSize(139, 50);

	button = new namelessgui::Button();
	button->signalClicked.connect(std::bind(&MainMenuState::slotNewGameClicked, this));
	button->setText("New Match");
	button->setSize(buttonSize);
	button->setParentAnchor({0.5f, 0.01f});
	button->setAnchor({0.5f, 0.0f});
	button->setRelativePosition({0.0f, 0.0f});
	mainWindow->addWidget(button);

	button = new namelessgui::Button();
	button->signalClicked.connect(std::bind(&MainMenuState::slotMapEditorClicked, this));
	button->setText("Map Editor");
	button->setSize(buttonSize);
	button->setParentAnchor({0.5f, 0.01});
	button->setAnchor({0.5f, 0.0f});
	button->setRelativePosition({0.0f, 50.0f});
	mainWindow->addWidget(button);

	button = new namelessgui::Button();
	button->setText("Settings");
	button->setSize(buttonSize);
	button->setParentAnchor({0.5f, 0.01f});
	button->setAnchor({0.5f, 0.0f});
	button->setRelativePosition({0.0f, 100.0f});
	mainWindow->addWidget(button);

	button = new namelessgui::Button();
	button->setText("About");
	button->setSize(buttonSize);
	button->setParentAnchor({0.5f, 0.01f});
	button->setAnchor({0.5f, 0.0f});
	button->setRelativePosition({0.0f, 150.0f});
	mainWindow->addWidget(button);

	button = new namelessgui::Button();
	button->signalClicked.connect(std::bind(&MainMenuState::slotQuitClicked, this));
	button->setText("Quit");
	button->setSize(buttonSize);
	button->setParentAnchor({0.5f, 0.01f});
	button->setAnchor({0.5f, 0.0f});
	button->setRelativePosition({0.0f, 200.0f});
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

	nextState_ = EGSID_NO_CHANGE;
}

EGameStateId MainMenuState::update()
{
	return nextState_;
}

void MainMenuState::draw()
{
	_renderWindow->draw(background_);
	_guiUptr->render(*_renderWindow, sf::RenderStates::Default);
}

} // namespace qrw

