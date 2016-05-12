#include "gamestates/skirmishstate.hpp"

namespace qrw
{

SkirmishState::SkirmishState(sf::RenderWindow* renderWindow)
    : SceneState(renderWindow, EGameStateId::EGSID_SKIRMISH_STATE)
{

}

void SkirmishState::init(GameState *previousState)
{
    SceneState::init(previousState);

    _board = std::make_shared<Board>(16, 9);
    _scene->setBoard(_board);
}

EGameStateId SkirmishState::update()
{
    if(_backToMainMenu)
        return EGameStateId::EGSID_MAIN_MENU_STATE;

    return EGameStateId::EGSID_NO_CHANGE;
}

} // namespace qrw
