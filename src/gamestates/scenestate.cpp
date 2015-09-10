#include "gamestates/scenestate.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace qrw
{

SceneState::SceneState(sf::RenderWindow* renderWindow, qrw::EGameStateId gameStateId)
	: GameState(renderWindow, gameStateId),
	  _scene(nullptr)
{
	_guiUptr->setVisible(true);

	// Set up back to main menu dialog
	_backToMainMenuDialog = new namelessgui::ConfirmationDialog("Really exit and go back to main menu?");
	_backToMainMenuDialog->signalYesClicked.connect(std::bind(&SceneState::slotBackToMainMenu, this));
	_backToMainMenuDialog->setAnchor({0.5f, 0.5f});
	_backToMainMenuDialog->setParentAnchor({0.5f, 0.5f});
	_guiUptr->addWidget(_backToMainMenuDialog);
	_backToMainMenuDialog->setVisible(false);
}

SceneState::~SceneState()
{
}

void SceneState::draw()
{
	_scene->render();
	_guiUptr->render(*_renderWindow, sf::RenderStates::Default);
}

bool SceneState::handleEvent(sf::Event& event)
{
	bool stopEventPropagation = GameState::handleEvent(event);

	if(event.type == sf::Event::KeyPressed)
		if(event.key.code == sf::Keyboard::Escape)
			_backToMainMenuDialog->setVisible(true);

	// Scene must only handle events that are not consumed by the gui.
	if(!stopEventPropagation)
		_scene->handleEvent(event);

	return stopEventPropagation;
}

void SceneState::slotBackToMainMenu()
{
	_backToMainMenu = true;
}

} // namespace qrw
