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

private:
	void slotUnitButtonChanged(const namelessgui::RadioToggleButton& unitButton);
	void slotCursorLeftClicked(const Coordinates& boardPosition);

	Board::Ptr _board;

	std::vector<Player::Ptr> _players;

	Player::Ptr _selectedPlayer;
	UNITTYPES _selectedUnitType;
};

} // namespace qrw

#endif // QRW_DEPLOYSTATE_HPP
