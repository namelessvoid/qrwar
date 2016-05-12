#ifndef SKIRMISHSTATE_H
#define SKIRMISHSTATE_H

#include "gamestates/scenestate.hpp"

#include "engine/board.hpp"

namespace qrw
{

class SkirmishState : public SceneState
{
public:
    SkirmishState(class sf::RenderWindow* renderWindow);

    virtual EGameStateId update() override;

    virtual void init(GameState* previousState) override;

private:
    virtual void slotCursorMoved(const Coordinates& boardPosition, bool isOnBoard) override;

    Board::Ptr _board;
};

} // namespace qrw

#endif // SKIRMISHSTATE_H
