#ifndef SKIRMISHSTATE_H
#define SKIRMISHSTATE_H

#include "game/states/scenestate.hpp"

#include "engine/board.hpp"
#include "engine/unit.hpp"
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
    SkirmishState(class sf::RenderWindow* renderWindow);

    virtual EGameStateId update() override;

    virtual void init(GameState* previousState) override;

	virtual void draw() override;

	virtual bool handleEvent(const Event &event) override;

private:
	virtual void slotCursorMoved(const Coordinates& boardPosition) override;
    virtual void slotCursorLeftClicked(const Coordinates& boardPosition) override;

	// Triggerd via signal of end turn button.
	void endTurn();

	void drawPath();

	void deselectUnit();

	void moveUnit();

	void performAttack(Unit* attackedUnit);

	void checkVictory();

	void replenishTroops();

	void updateSquareDetailWindow(const Coordinates& position);

    std::vector<Player::Ptr> _players;
	int _currentPlayer;
	namelessgui::Text* _playerNameText;

    Board* _board;

	Unit* _selectedUnit;

	std::shared_ptr<class Path> _path;

    class SquareDetailWindow* _squareDetailWindow;

	class SquareMarker* _squareMarker;

	std::unique_ptr<namelessgui::Gui> m_victoryGui;

	class VictoryDialog* m_victoryDialog;
};

} // namespace qrw

#endif // SKIRMISHSTATE_H
