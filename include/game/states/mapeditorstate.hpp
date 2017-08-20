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

	virtual bool handleEvent(sf::Event& event) override;

	Board* getBoard() const;

private:
    virtual void slotCursorLeftClicked(const Coordinates& boardPosition) override;
    virtual void slotCursorRightClicked(const Coordinates& boardPosition) override;

	void slotTerrainButtonChanged(const namelessgui::RadioToggleButton& activeTerrainButton);
	void slotToDeploymentButtonClicked();

	TERRAINTYPES _activeTerrainType;

	bool _toDeployment;

    /**
     * @brief Mode of the cursor.
     *
     * If set to true, terrain is removed. Otherwise, terrain is placed.
     */
    bool _eraseMode;

	Board* _spBoard;
};

} // namespace qrw

#endif // QRW_MAPEDITORSTATE_H
