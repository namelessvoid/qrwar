#ifndef QRW_DEPLOYSTATE_HPP
#define QRW_DEPLOYSTATE_HPP

#include <vector>

#include "gamestates/scenestate.hpp"

#include "engine/board.hpp"
#include "engine/player.hpp"
#include "engine/unittypes.hpp"

namespace namelessgui
{
class RadioToggleButton;
}

namespace qrw
{

class DeployState : public SceneState
{
public:
	DeployState(sf::RenderWindow* renderWindow);

	virtual ~DeployState();

	virtual qrw::EGameStateId update() override;

	virtual void init(GameState* previousState) override;

    /**
     * @brief Get the board.
     * @return Returns the board currently used by this game state.
     */
    Board::Ptr getBoard() const;

    /**
     * @brief Return the players.
     * @return Vector holding the players pointers.
     */
    std::vector<Player::Ptr> getPlayers() const;

private:
	void slotUnitButtonChanged(const namelessgui::RadioToggleButton& unitButton);
    void slotToSkirmishButtonClicked();

    virtual void slotCursorLeftClicked(const Coordinates& boardPosition) override;
	virtual void slotCursorRightClicked(const Coordinates& boardPosition) override;

	Board::Ptr _board;

	std::vector<Player::Ptr> _players;

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
