#ifndef QRW_SKIRMISHPREPARATIONSTATE_HPP
#define QRW_SKIRMISHPREPARATIONSTATE_HPP

#include "gamestates/gamestate.hpp"

#include "game/skirmish/mapmanager.hpp"

namespace namelessgui {
class ConfirmationDialog;
class LineInput;
}

namespace qrw {

class SkirmishPreparationState : public GameState, public EventHandler

{
public:
    SkirmishPreparationState(sf::RenderWindow* renderWindow, MapManager& mapManager);

    virtual ~SkirmishPreparationState();

    virtual EGameStateId update() override;
    virtual void draw() override;

	virtual bool handleEvent(const IEvent &event) override;

	const std::string& getMapName() const { return selectedMap_; }

	const std::string& getPlayerOneName() const;

	const std::string& getPlayerTwoName() const;

private:
    SkirmishPreparationState(const SkirmishPreparationState& rhs) = delete;

    SkirmishPreparationState& operator=(const SkirmishPreparationState& rhs) = delete;

	void slotMapSelected(const std::string& mapName) { selectedMap_ = mapName; }

	void slotToSkirmishStateClicked() { nextState_ = EGSID_DEPLOY_STATE; }

    void slotBackToMainMenuClicked() { nextState_ = EGSID_MAIN_MENU_STATE; }

    MapManager& mapManager_;

	std::string selectedMap_;

    namelessgui::ConfirmationDialog* backToMainMenuDialog_;

    EGameStateId nextState_;

	namelessgui::LineInput* playerOneName_;
	namelessgui::LineInput* playerTwoName_;
};


} // namespace qrw

#endif // QRW_SKIRMISHPREPARATIONSTATE_HPP
