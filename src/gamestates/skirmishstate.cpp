#include "gamestates/skirmishstate.hpp"

#include "gamestates/deploystate.hpp"
#include "gui/texturemanager.hpp"
#include "gui/ng/label.hpp"
#include "gui/ng/spritewidget.hpp"
#include "gui/squaredetailwindow.hpp"

namespace qrw
{

SkirmishState::SkirmishState(sf::RenderWindow* renderWindow)
    : SceneState(renderWindow, EGameStateId::EGSID_SKIRMISH_STATE)
{
    _squareDetailWindow = new SquareDetailWindow();
    _guiUptr->addWidget(_squareDetailWindow);
}

void SkirmishState::init(GameState *previousState)
{
    SceneState::init(previousState);

    if(previousState->getId() != EGameStateId::EGSID_DEPLOY_STATE)
        return;

    DeployState* deployState = static_cast<DeployState*>(previousState);

    _board = deployState->getBoard();
    _scene->setBoard(_board);

    // TODO: reset square detail window
}

EGameStateId SkirmishState::update()
{
    if(_backToMainMenu)
        return EGameStateId::EGSID_MAIN_MENU_STATE;

    return EGameStateId::EGSID_NO_CHANGE;
}

void SkirmishState::slotCursorMoved(const Coordinates &boardPosition, bool isOnBoard)
{
    if(isOnBoard)
        _squareDetailWindow->setSquare(_board->getSquare(boardPosition));
    else
        _squareDetailWindow->setSquare(nullptr);
}

} // namespace qrw
