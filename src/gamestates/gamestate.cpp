#include "gamestates/gamestate.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace qrw
{

GameState::GameState(sf::RenderWindow *renderWindow)
{
	this->_renderWindow = renderWindow;
}

} // namespace qrw
