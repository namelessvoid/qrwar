#include "qrwar.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "config/settings.hpp"
#include "config/tilesetprocessor.hpp"

#include "gui/texturemanager.hpp"

#include "gamestates/introstate.hpp"
#include "gamestates/mainmenustate.hpp"
#include "gamestates/mapeditorstate.hpp"
#include "gamestates/deploystate.hpp"
#include "gamestates/skirmishstate.hpp"

namespace qrw
{

QRWar::QRWar()
{
	// Load resources
	preloadResources();


	// Initialize game states
	GameState* gameState;

	// Intro state
	gameState = new IntroState(&_renderWindow);
	_gameStates[gameState->getId()] = gameState;

	// Main menu state
	gameState = new MainMenuState(&_renderWindow);
	_gameStates[gameState->getId()] = gameState;

	// Map editor state
	gameState = new MapEditorState(&_renderWindow);
	_gameStates[gameState->getId()] = gameState;

	// Deploy state
	gameState = new DeployState(&_renderWindow);
	_gameStates[gameState->getId()] = gameState;

    // Skirmish state
    gameState = new SkirmishState(&_renderWindow);
    _gameStates[gameState->getId()] = gameState;

	// Set and initialize start state
	_currentState = _gameStates[EGameStateId::EGSID_INTRO_STATE];
	_currentState->init(nullptr);
}

QRWar::~QRWar()
{
	for(auto iter : _gameStates)
		delete iter.second;
}

void QRWar::run()
{
	sf::Event event;
	bool quit = false;
	EGameStateId nextStateId;

	while(!quit)
	{
		_renderWindow.clear(sf::Color::Black);

		while(_renderWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                quit = true;

			_currentState->handleEvent(event);
        }

		nextStateId = _currentState->update();

		// Quit the application
		if(nextStateId == EGameStateId::EGSID_QUIT)
			quit = true;
		// If no state change occured: draw the current state
		else if(nextStateId == EGameStateId::EGSID_NO_CHANGE)
		{
			_currentState->draw();
			_renderWindow.display();
		}
		// Perform a state change
		else
		{
			GameState* previousState = _currentState;
			_currentState = _gameStates[nextStateId];
			_currentState->init(previousState);
		}
	}
}

void QRWar::preloadResources()
{
	// Start initialization of qrw...
	// Load Settings
	qrw::Settings* settings = qrw::Settings::getInstance();
	settings->loadFromFile();

	TextureManager::getInstance()->loadTexture("mainmenubackground", "./res/img/mainmenubackground.png");

	// Loading tilesets
	qrw::TilesetProcessor tilesetprocessor;
	tilesetprocessor.loadTileset(settings->getEntityTilesetPath());
	tilesetprocessor.loadTileset(settings->getGuiTilesetPath());
}

} // namespace qrw
