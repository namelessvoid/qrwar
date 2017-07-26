#ifndef QRW_SCENESTATE_HPP
#define QRW_SCENESTATE_HPP

#include "gamestates/gamestate.hpp"

#include "gui/scene.hpp"

#include "gui/ng/confirmationdialog.hpp"

namespace qrw
{

class SceneState : public GameState
{
public:
	virtual ~SceneState();

	virtual void init(GameState* previousState) override;

	virtual void draw() override;

	virtual bool handleEvent(sf::Event& event) override;

protected:
	SceneState(sf::RenderWindow* renderWindow, EGameStateId gameStateId);

	namelessgui::Window* _toolBar;

	bool _backToMainMenu;

    virtual void slotCursorLeftClicked(const Coordinates& boardPosition) {}
    virtual void slotCursorRightClicked(const Coordinates& boardPosition) {}
    virtual void slotCursorMoved(const Coordinates& boardPosition, bool isOnBoard) {}

private:
	void slotBackToMainMenu();

	namelessgui::ConfirmationDialog* _backToMainMenuDialog;
};

} // namespace qrw

#endif // QRW_SCENESTATE_HPP
