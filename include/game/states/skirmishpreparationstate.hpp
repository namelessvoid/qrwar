#ifndef QRW_SKIRMISHPREPARATIONSTATE_HPP
#define QRW_SKIRMISHPREPARATIONSTATE_HPP

#include "gamestates/gamestate.hpp"

#include "game/skirmish/mapmanager.hpp"

#include "game/skirmish/gui/skirmishguifactory.hpp"

namespace namelessgui {
class ConfirmationDialog;
class MessageDialog;
}

namespace qrw {

class SkirmishPreparationState : public GameState, public EventHandler

{
public:
    SkirmishPreparationState(sf::RenderWindow* renderWindow, MapManager& mapManager, const SkirmishGuiFactory& guiFactory);

    EGameStateId update() override;
    void draw() override;

	bool handleEvent(const IEvent &event) override;

	const std::string& getMapName() const;
	const std::string& getPlayerOneName() const;
	const std::string& getPlayerTwoName() const;

	void init(GameState* previousState) override;

private:
    SkirmishPreparationState(const SkirmishPreparationState& rhs) = delete;

    SkirmishPreparationState& operator=(const SkirmishPreparationState& rhs) = delete;

	void slotToSkirmishStateClicked() { nextState_ = EGSID_DEPLOY_STATE; }

    void slotBackToMainMenuClicked() { nextState_ = EGSID_MAIN_MENU_STATE; }

    MapManager& mapManager_;

    namelessgui::ConfirmationDialog* backToMainMenuDialog_;
    namelessgui::MessageDialog* noMapsDialog_;

    EGameStateId nextState_;

    SkirmishPreparationGui* skirmishPreparationWindow_;
};


} // namespace qrw

#endif // QRW_SKIRMISHPREPARATIONSTATE_HPP
