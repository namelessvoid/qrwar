#ifndef QRW_MAPEDITORSTATE_H
#define QRW_MAPEDITORSTATE_H

#include <memory>

#include "gamestates/gamestate.hpp"

#include "gui/ng/confirmationdialog.hpp"
#include "gui/ng/spritewidget.hpp"
#include "gui/ng/radiotogglebutton.hpp"

#include "gui/cursor.hpp"

#include "engine/board.hpp"

namespace qrw
{

class MapEditorState : public GameState
{
public:
	MapEditorState(sf::RenderWindow* renderWindow);

	virtual ~MapEditorState();

	virtual void init(GameState *previousState);

	virtual EGameStateId update();

	virtual void draw();

	virtual bool handleEvent(sf::Event& event) override;

private:
	void slotBackToMainMenu();
	void slotCursorLeftClicked();
	void slotCursorRightClicked();
	void slotTerrainButtonChanged(namelessgui::RadioToggleButton* activeTerrainButton);

	namelessgui::ConfirmationDialog* _backToMainMenuDialog;
	namelessgui::Window* _toolBar;

	namelessgui::RadioToggleButton* _activeTerrainButton;

	bool _backToMainMenu;

	namelessgui::RectangularWidget _background;
	Cursor _cursor;

	std::shared_ptr<Board> _spBoard;
};

} // namespace qrw

#endif // QRW_MAPEDITORSTATE_H
