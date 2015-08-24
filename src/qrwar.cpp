#include "qrwar.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "gamestates/intro.hpp"

namespace qrw
{

QRWar::QRWar()
{
	// Create render window
	_renderWindow.create(
		sf::VideoMode(640, 480),
		"Quad-Ruled War - Loading...",
		sf::Style::None
	);

	// Initialize game states
	GameState* gameState;

	gameState = new IntroState(&_renderWindow);
	_gameStates[gameState->getId()] = gameState;
}

void QRWar::run()
{
	while(true);
}

} // namespace qrw
