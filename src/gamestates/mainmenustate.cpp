#include "gamestates/mainmenustate.hpp"

namespace qrw
{

MainMenuState::MainMenuState(sf::RenderWindow* renderWindow)
	: GameState(renderWindow, EGameStateId::EGSID_MAIN_MENU_STATE)
{

}

void MainMenuState::init(GameState* previousState)
{

}

EGameStateId MainMenuState::update()
{
	return EGameStateId::EGSID_NO_CHANGE;
}

void MainMenuState::draw()
{

}

void MainMenuState::handleEvent(sf::Event& event)
{

}

} // namespace qrw

