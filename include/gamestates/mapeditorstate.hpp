#ifndef QRW_MAPEDITORSTATE_H
#define QRW_MAPEDITORSTATE_H

#include <memory>
#include <map>

#include "gamestates/gamestate.hpp"

#include "engine/terraintypes.hpp"

#include "gui/ng/confirmationdialog.hpp"
#include "gui/ng/spritewidget.hpp"
#include "gui/ng/radiotogglebutton.hpp"

#include "gui/scene.hpp"
#include "gui/cursor.hpp"
#include "gui/terrainentity.hpp"

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
	void slotCursorLeftClicked(const Coordinates& boardPosition);
	void slotCursorRightClicked(const Coordinates& boardPosition);
	void slotTerrainButtonChanged(const namelessgui::RadioToggleButton& activeTerrainButton);
	void slotToDeploymentButtonClicked();

	namelessgui::ConfirmationDialog* _backToMainMenuDialog;
	namelessgui::Window* _toolBar;

	TERRAINTYPES _activeTerrainType;

	bool _toDeployment;
	bool _backToMainMenu;

	std::unique_ptr<Scene> _scene;



	std::shared_ptr<Board> _spBoard;

	std::map<const Coordinates, TerrainEntity::Ptr> _terrainEntities;
};

} // namespace qrw

#endif // QRW_MAPEDITORSTATE_H
