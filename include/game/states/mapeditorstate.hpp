#ifndef QRW_MAPEDITORSTATE_H
#define QRW_MAPEDITORSTATE_H

#include <memory>
#include <vector>

#include "game/states/scenestate.hpp"

#include "game/skirmish/toggleflatmodehandler.hpp"
#include "game/skirmish/mapmanager.hpp"
#include "game/skirmish/structurefactory.hpp"

#include "game/skirmish/gui/skirmishguifactory.hpp"

#include "engine/terraintypes.hpp"
#include "engine/board.hpp"

#include "gui/ng/confirmationdialog.hpp"
#include "gui/ng/spritewidget.hpp"
#include "gui/ng/radiotogglebutton.hpp"

#include "gui/cursor.hpp"

namespace qrw
{

class MapEditorState : public SceneState
{
public:
	MapEditorState(sf::RenderWindow* renderWindow, MapManager& mapManager, SkirmishGuiFactory& guiFactory);

	void init(GameState *previousState) override;

	EGameStateId update() override;

private:
    void slotCursorLeftClicked(const Coordinates& boardPosition) override;
    void slotCursorRightClicked(const Coordinates& boardPosition) override;

	void slotChangeBoardWidth(unsigned int width);
	void slotChangeBoardHeight(unsigned int height);
	void despawnTerrainNotOnBoard();
	void despawnStructuresNotOnBoard();
	void cropDeploymentZones();

	void setCursorModePlaceTerrain(TERRAINTYPES terrainType);
	void setCursorModeEraseterrain();
	void setCursorModePlaceStructure(Structure::Type type);
	void setCursorModeEraseStructure();
	void setCursorModePlaceDeploymentZone(unsigned int playerNumber);
	void setCursorModeEraseDeploymentZone();

	void placeTerrain(const Coordinates& boardPosition, TERRAINTYPES terrainType);
	void eraseTerrain(const Coordinates& boardPosition);
	void placeStructure(const Coordinates& position, Structure::Type structureId);
	void eraseStructure(const Coordinates& position);
	void placeDeploymentZone(const Coordinates& boardPosition, unsigned int playerNumber);
	void eraseDeploymentZone(const Coordinates& boardPosition);

	void slotSaveClicked(const std::string& mapName);
	void slotLoadClicked(const std::string& mapName);

	ToggleFlatModeHandler toggleFlatModeHandler_;

	void saveMap(const std::string(&mapName));
	std::string mapNameForSaveConfirmation_;

	MapManager& mapManager;
	StructureFactory structureFactory_;

	namelessgui::ConfirmationDialog* mapOverwriteConfirmationDialog_;

	std::vector<class DeploymentZone*> deploymentZones_;

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
		Structure::Type structure;
		unsigned int playerNumber;
	} selectedEntity_;


	Board* _spBoard;

	const unsigned int INITIAL_BOARD_WIDTH = 16;
	const unsigned int INITIAL_BOARD_HEIGHT = 10;
};

} // namespace qrw

#endif // QRW_MAPEDITORSTATE_H
