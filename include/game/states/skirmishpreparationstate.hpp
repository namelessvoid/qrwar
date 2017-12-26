#ifndef QRW_SKIRMISHPREPARATIONSTATE_HPP
#define QRW_SKIRMISHPREPARATIONSTATE_HPP

#include "gamestates/gamestate.hpp"

namespace namelessgui {
class Window;
}

namespace qrw {

class SkirmishPreparationState : public GameState
{
public:
    SkirmishPreparationState(sf::RenderWindow* renderWindow);

    virtual ~SkirmishPreparationState();

    virtual EGameStateId update() override;
    virtual void draw() override;

private:
    SkirmishPreparationState(const SkirmishPreparationState& rhs) = delete;

    SkirmishPreparationState& operator=(const SkirmishPreparationState& rhs) = delete;

    void slotToSkirmishStateClicked();

    namelessgui::Window* window_;

    bool toSkirmishState_;
};


} // namespace qrw

#endif // QRW_SKIRMISHPREPARATIONSTATE_HPP
