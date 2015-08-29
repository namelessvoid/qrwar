#include "qrwar.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "gamestates/introstate.hpp"
#include "gamestates/mainmenustate.hpp"
#include "gamestates/mapeditorstate.hpp"

namespace qrw
{

QRWar::QRWar()
{
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


	// Set and initialize start state
	_currentState = _gameStates[EGameStateId::EGSID_INTRO_STATE];
	_currentState->init(nullptr);
}

QRWar::~QRWar()
{
	delete _gameStates.at(EGameStateId::EGSID_INTRO_STATE);
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
			_currentState->handleEvent(event);

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

} // namespace qrw
