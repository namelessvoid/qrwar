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

namespace namelessgui {
class LineInput;
}

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

	void setCursorModePlaceTerrain(TERRAINTYPES terrainType);
	void setCursorModeEraseterrain();
	void setCursorModePlaceDeploymentZone(unsigned int playerNumber);
	void setCursorModeEraseDeploymentZone();

	void slotSaveButtonClicked();
	void slotLoadButtonClicked();

	void saveMap();

	namelessgui::Window* createConfigToolsWindow();
	namelessgui::Window* createTerrainToolsWindow();
	namelessgui::Window* createStructureToolsWindow();
	namelessgui::Window* createDeploymentZoneToolsWindow();

	namelessgui::LineInput* mapNameInput_;

	namelessgui::ConfirmationDialog* mapOverwriteConfirmationDialog_;

    /**
     * @brief Mode of the cursor.
     *
     * If set to true, terrain is removed. Otherwise, terrain is placed.
     */
	enum class CursorMode
	{
		PLACE_TERRAIN,
		ERASE_TERRAIN,

		PLACE_STRUCTURE,
		ERASE_STRUCTURE,

		PLACE_DEPLOYMENTZONE,
		ERASE_DEPLOYMENTZONE
	} cursorMode_;

	union SelectedEntity
	{
		TERRAINTYPES terrainType;
		unsigned int playerNumber;
	} selectedEntity_;


	Board* _spBoard;

	const unsigned int INITIAL_BOARD_WIDTH = 16;
	const unsigned int INITIAL_BOARD_HEIGHT = 10;
};

} // namespace qrw

#endif // QRW_MAPEDITORSTATE_H
