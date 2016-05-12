#include "gamestates/skirmishstate.hpp"

#include "gamestates/deploystate.hpp"

#include <iostream>

namespace qrw
{

SkirmishState::SkirmishState(sf::RenderWindow* renderWindow)
    : SceneState(renderWindow, EGameStateId::EGSID_SKIRMISH_STATE)
{

}

void SkirmishState::init(GameState *previousState)
{
    SceneState::init(previousState);

    if(previousState->getId() != EGameStateId::EGSID_DEPLOY_STATE)
        return;

    DeployState* deployState = static_cast<DeployState*>(previousState);

    _board = deployState->getBoard();
    _scene->setBoard(_board);
}

void SkirmishState::slotCursorMoved(const Coordinates &boardPosition, bool isOnBoard)
{
    std::cout << "Cursor moved to: " << boardPosition.getX() << "/" << boardPosition.getY() << std::endl << std::flush;
}

EGameStateId SkirmishState::update()
{
    if(_backToMainMenu)
        return EGameStateId::EGSID_MAIN_MENU_STATE;

    return EGameStateId::EGSID_NO_CHANGE;
}

} // namespace qrw
