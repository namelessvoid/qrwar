#include "gamestates/gamestate.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace qrw
{

GameState::GameState(sf::RenderWindow* renderWindow, EGameStateId id)
	: _renderWindow(renderWindow),
	  _id(id)
{
}

GameState::~GameState()
{
}

EGameStateId GameState::getId()
{
	return _id;
}

} // namespace qrw
