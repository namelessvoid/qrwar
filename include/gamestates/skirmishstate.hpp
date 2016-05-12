#ifndef SKIRMISHSTATE_H
#define SKIRMISHSTATE_H

#include "gamestates/scenestate.hpp"

#include "engine/board.hpp"

// Foreward declarations
//namespace sf
//{
//    class RenderWindow;
//}

namespace qrw
{

class SkirmishState : public SceneState
{
public:
    SkirmishState(class sf::RenderWindow* renderWindow);

    virtual EGameStateId update() override;

    virtual void init(GameState* previousState) override;

private:
    Board::Ptr _board;
};

} // namespace qrw

#endif // SKIRMISHSTATE_H
