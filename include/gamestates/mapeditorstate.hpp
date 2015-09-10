#ifndef QRW_MAPEDITORSTATE_H
#define QRW_MAPEDITORSTATE_H

#include <memory>

#include "gamestates/scenestate.hpp"

#include "engine/terraintypes.hpp"

#include "gui/ng/confirmationdialog.hpp"
#include "gui/ng/spritewidget.hpp"
#include "gui/ng/radiotogglebutton.hpp"

#include "gui/cursor.hpp"
#include "gui/terrainentity.hpp"

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

	virtual bool handleEvent(sf::Event& event) override;

	Board::Ptr getBoard() const;

private:
	void slotCursorLeftClicked(const Coordinates& boardPosition);
	void slotCursorRightClicked(const Coordinates& boardPosition);
	void slotTerrainButtonChanged(const namelessgui::RadioToggleButton& activeTerrainButton);
	void slotToDeploymentButtonClicked();

	namelessgui::Window* _toolBar;

	TERRAINTYPES _activeTerrainType;

	bool _toDeployment;

	std::shared_ptr<Board> _spBoard;
};

} // namespace qrw

#endif // QRW_MAPEDITORSTATE_H
