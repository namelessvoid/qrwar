#ifndef SKIRMISHSTATE_H
#define SKIRMISHSTATE_H

#include "game/states/scenestate.hpp"

#include "engine/board.hpp"
#include "game/skirmish/toggleflatmodehandler.hpp"
#include "game/skirmish/unit.hpp"
#include "engine/player.hpp"

#include <vector>
#include <memory>

namespace namelessgui
{
class Text;
}

namespace qrw
{

class SkirmishState : public SceneState
{
public:
    explicit SkirmishState(class sf::RenderWindow* renderWindow);

    EGameStateId update() override;

    void init(GameState* previousState) override;

	void draw() override;

	bool handleEvent(const IEvent &event) override;

private:
	ToggleFlatModeHandler toggleFlatModeHandler_;
	void slotCursorMoved(const Coordinates& boardPosition) override;
	void slotCursorLeftClicked(const Coordinates& boardPosition) override;

	// Triggerd via signal of end turn button.
	void endTurn();

	void deselectSquare();

	void checkVictory();

	void replenishTroops();

    std::vector<Player::Ptr> _players;
	int _currentPlayer;
	namelessgui::Text* _playerNameText;

    Board* _board;

	Unit* _selectedUnit;

    class SquareDetailWindow* _squareDetailWindow;

	class SquareMarker* _squareMarker;

	std::unique_ptr<namelessgui::Gui> m_victoryGui;

	class VictoryDialog* m_victoryDialog;
};

} // namespace qrw

#endif // SKIRMISHSTATE_H
