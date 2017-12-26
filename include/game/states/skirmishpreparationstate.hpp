#ifndef QRW_SKIRMISHPREPARATIONSTATE_HPP
#define QRW_SKIRMISHPREPARATIONSTATE_HPP

#include "gamestates/gamestate.hpp"

namespace namelessgui {
class ConfirmationDialog;
}

namespace qrw {

class SkirmishPreparationState : public GameState, public EventHandler

{
public:
    SkirmishPreparationState(sf::RenderWindow* renderWindow);

    virtual ~SkirmishPreparationState();

    virtual EGameStateId update() override;
    virtual void draw() override;

    virtual bool handleEvent(const Event &event) override;

private:
    SkirmishPreparationState(const SkirmishPreparationState& rhs) = delete;

    SkirmishPreparationState& operator=(const SkirmishPreparationState& rhs) = delete;

    void slotToSkirmishStateClicked() { nextState_ = EGSID_SKIRMISH_STATE; }

    void slotBackToMainMenuClicked() { nextState_ = EGSID_MAIN_MENU_STATE; }

    namelessgui::ConfirmationDialog* backToMainMenuDialog_;

    EGameStateId nextState_;
};


} // namespace qrw

#endif // QRW_SKIRMISHPREPARATIONSTATE_HPP
