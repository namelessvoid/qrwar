#ifndef SKIRMISHSTATE_H
#define SKIRMISHSTATE_H

#include "gamestates/scenestate.hpp"

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

private:
    virtual void slotCursorMoved(const Coordinates& boardPosition, bool isOnBoard) override;
    virtual void slotCursorLeftClicked(const Coordinates& boardPosition) override;

	virtual bool handleEvent(sf::Event &event);

	// Triggerd via signal of end turn button.
	void endTurn();

	void drawPath();

	void deselectUnit();

	void moveUnit();

	void performAttack(std::shared_ptr<Unit> attackedUnit);

	void replenishTroops();

	void updateSquareDetailWindow(const Coordinates& position);

    std::vector<Player::Ptr> _players;
	int _currentPlayer;
	namelessgui::Text* _playerNameText;

    Board::Ptr _board;

    Unit::Ptr _selectedUnit;

	std::shared_ptr<class Path> _path;

    class SquareDetailWindow* _squareDetailWindow;

	std::unique_ptr<class SquareMarker> _squareMarker;
};

} // namespace qrw

#endif // SKIRMISHSTATE_H
