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

	virtual void draw() override;

	virtual bool handleEvent(sf::Event& event) override;

protected:
	SceneState(sf::RenderWindow* renderWindow, EGameStateId gameStateId);

	std::unique_ptr<Scene> _scene;

	namelessgui::Window* _toolBar;

	bool _backToMainMenu;

private:
	void slotBackToMainMenu();

	namelessgui::ConfirmationDialog* _backToMainMenuDialog;
};

} // namespace qrw

#endif // QRW_SCENESTATE_HPP
