#ifndef QRW_DEPLOYSTATE_HPP
#define QRW_DEPLOYSTATE_HPP

#include <vector>

#include "game/skirmish/toggleflatmodehandler.hpp"
#include "game/skirmish/mapmanager.hpp"
#include "game/states/scenestate.hpp"

#include "engine/board.hpp"
#include "engine/player.hpp"
#include "game/skirmish/unittypes.hpp"

#include "gui/ng/messagedialog.hpp"

namespace namelessgui
{
class RadioToggleButton;
class Text;
}

namespace qrw
{
class DeploymentZone;

class DeployState : public SceneState
{
public:
	DeployState(sf::RenderWindow* renderWindow, MapManager& mapManager);

	virtual ~DeployState();

	virtual qrw::EGameStateId update() override;

	virtual void init(GameState* previousState) override;

    /**
     * @brief Get the board.
     * @return Returns the board currently used by this game state.
     */
    Board* getBoard() const;

    /**
     * @brief Return the players.
     * @return Vector holding the players pointers.
     */
    std::vector<Player::Ptr> getPlayers() const;

private:
	ToggleFlatModeHandler toggleFlatModeHandler_;

	void slotUnitButtonChanged(UNITTYPES unittype, unsigned int playerNumber);
    void slotToSkirmishButtonClicked();

    virtual void slotCursorLeftClicked(const Coordinates& boardPosition) override;
	virtual void slotCursorRightClicked(const Coordinates& boardPosition) override;

    void handleMapLoadingError();

    MapManager& mapManager_;

	Board* board_;
    std::map<int, DeploymentZone*> deploymentZones_;

	std::vector<Player::Ptr> _players;

	namelessgui::Text* playerOneNameLabel_;
	namelessgui::Text* playerTwoNameLabel_;

    namelessgui::MessageDialog* errorDialog_;

    /**
     * @brief If set to true, the update method will cause the game to switch
     * to SkirmishState.
     */
    bool _toSkirmish;

	Player::Ptr _selectedPlayer;
	UNITTYPES _selectedUnitType;
};

} // namespace qrw

#endif // QRW_DEPLOYSTATE_HPP
