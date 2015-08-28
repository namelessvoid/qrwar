#include "gamestates/mainmenustate.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/BlendMode.hpp>
#include <SFML/Window/Event.hpp>

#include "config/settings.hpp"
#include "gui/texturemanager.hpp"
#include "gui/ng/button.hpp"

namespace qrw
{

MainMenuState::MainMenuState(sf::RenderWindow* renderWindow)
	: GameState(renderWindow, EGameStateId::EGSID_MAIN_MENU_STATE),
	  _quitClicked(false),
	  _mainWindow()
{
	_mainWindow.setSize(sf::Vector2f(145, 204));
	_mainWindow.setRelativePosition(sf::Vector2f(15, 15));

	namelessgui::Button* button;
	sf::Vector2f buttonSize(139, 50);


	button = new namelessgui::Button();
	button->setText("New Match");
	button->setSize(buttonSize);
	button->setParentAnchor({0.5f, 0.01f});
	button->setAnchor({0.5f, 0.0f});
	button->setRelativePosition({0.0f, 0.0f});
	_mainWindow.addWidget(button);

	button = new namelessgui::Button();
	button->setText("Settings");
	button->setSize(buttonSize);
	button->setParentAnchor({0.5f, 0.01f});
	button->setAnchor({0.5f, 0.0f});
	button->setRelativePosition({0.0f, 50.0f});
	_mainWindow.addWidget(button);

	button = new namelessgui::Button();
	button->setText("About");
	button->setSize(buttonSize);
	button->setParentAnchor({0.5f, 0.01f});
	button->setAnchor({0.5f, 0.0f});
	button->setRelativePosition({0.0f, 100.0f});
	_mainWindow.addWidget(button);

	button = new namelessgui::Button();
	button->setText("Quit");
	button->setSize(buttonSize);
	button->signalclicked.connect(std::bind(&MainMenuState::quitClicked, this));
	button->setParentAnchor({0.5f, 0.01f});
	button->setAnchor({0.5f, 0.0f});
	button->setRelativePosition({0.0f, 150.0f});
	_mainWindow.addWidget(button);

	_mainWindow.setVisible(true);
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
	if(_quitClicked)
		return EGSID_QUIT;
	return EGSID_NO_CHANGE;
}

void MainMenuState::draw()
{
	_renderWindow->draw(_background);
	_mainWindow.render(*_renderWindow, sf::RenderStates::Default);
}

void MainMenuState::handleEvent(sf::Event& event)
{
	if(event.type == sf::Event::Resized)
		_renderWindow->setView(sf::View(sf::FloatRect(0.0f, 0.0f, event.size.width, event.size.height)));
	_mainWindow.handleEvent(event);
}

void MainMenuState::quitClicked()
{
	_quitClicked = true;
}

} // namespace qrw

