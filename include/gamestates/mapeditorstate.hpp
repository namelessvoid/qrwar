#ifndef QRW_MAPEDITORSTATE_H
#define QRW_MAPEDITORSTATE_H

#include <memory>

#include "gamestates/gamestate.hpp"
#include "gui/ng/confirmationdialog.hpp"
#include "gui/ng/spritewidget.hpp"
#include "gui/ng/buttongroup.hpp"

#include "engine/board.hpp"

namespace qrw
{

class MapEditorState : public GameState
{
public:
	MapEditorState(sf::RenderWindow* renderWindow);

	virtual void init(GameState *previousState);

	virtual EGameStateId update();

	virtual void draw();

	virtual void handleEvent(sf::Event& event);

private:
	void slotBackToMainMenu();

	bool _menusInitialized;

	namelessgui::ConfirmationDialog _backToMainMenuDialog;
	namelessgui::Window _toolBar;
	namelessgui::ButtonGroup _terrainButtonGroup;

	bool _backToMainMenu;

	namelessgui::RectangularWidget _background;

	std::shared_ptr<Board> _spBoard;
};

} // namespace qrw

#endif // QRW_MAPEDITORSTATE_H
