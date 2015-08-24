#include "qrwar.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "gamestates/intro.hpp"

namespace qrw
{

QRWar::QRWar()
{
	// Initialize game states
	GameState* gameState;

	gameState = new IntroState(&_renderWindow);
	_gameStates[gameState->getId()] = gameState;
	_currentState = gameState;
	_currentState->init(nullptr);
}

QRWar::~QRWar()
{
	delete _gameStates.at(EGameStateId::EGSID_INTRO);
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

		if(nextStateId == EGameStateId::EGSID_QUIT)
			quit = true;
		else
		{
			_currentState->draw();
			_renderWindow.display();
		}
	}
}

} // namespace qrw
