#ifndef QRW_MAPEDITORSTATE_H
#define QRW_MAPEDITORSTATE_H

#include <memory>

#include "game/states/scenestate.hpp"

#include "engine/terraintypes.hpp"

#include "gui/ng/confirmationdialog.hpp"
#include "gui/ng/spritewidget.hpp"
#include "gui/ng/radiotogglebutton.hpp"

#include "gui/cursor.hpp"

#include "engine/board.hpp"

namespace qrw
{

class MapEditorState : public SceneState
{
public:
	MapEditorState(sf::RenderWindow* renderWindow);

	virtual ~MapEditorState();

	virtual void init(GameState *previousState);

	virtual EGameStateId update();

	Board* getBoard() const;

private:
    virtual void slotCursorLeftClicked(const Coordinates& boardPosition) override;
    virtual void slotCursorRightClicked(const Coordinates& boardPosition) override;

	void slotChangeBoardWidth(unsigned int width);
	void slotChangeBoardHeight(unsigned int height);
	void despawnTerrainNotOnBoard();

	void slotTerrainButtonChanged(const namelessgui::RadioToggleButton& activeTerrainButton);
	void slotSaveButtonClicked();

	namelessgui::Window* createConfigToolsWindow();
	namelessgui::Window* createTerrainToolsWindow();
	namelessgui::Window* createStructureToolsWindow();

	TERRAINTYPES _activeTerrainType;

    /**
     * @brief Mode of the cursor.
     *
     * If set to true, terrain is removed. Otherwise, terrain is placed.
     */
    bool _eraseMode;

	Board* _spBoard;

	const unsigned int INITIAL_BOARD_WIDTH = 16;
	const unsigned int INITIAL_BOARD_HEIGHT = 8;
};

} // namespace qrw

#endif // QRW_MAPEDITORSTATE_H
