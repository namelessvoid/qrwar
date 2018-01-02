#ifndef QRW_SCENESTATE_HPP
#define QRW_SCENESTATE_HPP

#include "gamestates/gamestate.hpp"

#include "gui/scene.hpp"

#include "gui/ng/confirmationdialog.hpp"

#include "eventsystem/eventhandler.hpp"

namespace qrw
{

class SceneState : public GameState, public EventHandler
{
public:
	virtual ~SceneState();

	virtual void init(GameState* previousState) override;

	virtual void draw() override;

	virtual bool handleEvent(const IEvent& event) override;

	void slotBackToMainMenu();

protected:
	SceneState(sf::RenderWindow* renderWindow, EGameStateId gameStateId);

	namelessgui::Window* _toolBar;

	bool _backToMainMenu;

    virtual void slotCursorLeftClicked(const Coordinates& boardPosition) {}
    virtual void slotCursorRightClicked(const Coordinates& boardPosition) {}
	virtual void slotCursorMoved(const Coordinates& boardPosition) {}

private:
	namelessgui::ConfirmationDialog* _backToMainMenuDialog;
};

} // namespace qrw

#endif // QRW_SCENESTATE_HPP
