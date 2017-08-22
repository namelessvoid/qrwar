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

	virtual bool handleEvent(sf::Event& event) override;

	virtual bool handleEvent(const Event& event) override;

protected:
	SceneState(sf::RenderWindow* renderWindow, EGameStateId gameStateId);

	class Cursor* m_cursor;

	namelessgui::Window* _toolBar;

	bool _backToMainMenu;

    virtual void slotCursorLeftClicked(const Coordinates& boardPosition) {}
    virtual void slotCursorRightClicked(const Coordinates& boardPosition) {}
	virtual void slotCursorMoved(const Coordinates& boardPosition) {}

private:
	void slotBackToMainMenu();

	namelessgui::ConfirmationDialog* _backToMainMenuDialog;
};

} // namespace qrw

#endif // QRW_SCENESTATE_HPP
