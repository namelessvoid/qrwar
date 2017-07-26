#include "gamestates/scenestate.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "config/settings.hpp"

namespace qrw
{

SceneState::SceneState(sf::RenderWindow* renderWindow, qrw::EGameStateId gameStateId)
	: GameState(renderWindow, gameStateId)
{
	// Initialize toolbar
	_toolBar = new namelessgui::Window();
	_toolBar->setVisible(true);
	_toolBar->setSize({150.0f, (float)Settings::getInstance()->getResolutionY()});
	_toolBar->setAnchor({1.0f, 0.0f});
	_toolBar->setParentAnchor({1.0f, 0.0f});
	_toolBar->setVisible(true);
	_guiUptr->addWidget(_toolBar);

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

void SceneState::init(GameState* previousState)
{
	_backToMainMenu = false;

	// Set up cursor signals
	g_scene.getCursor().signalLeftClicked.connect(std::bind(&SceneState::slotCursorLeftClicked, this, std::placeholders::_1));
	g_scene.getCursor().signalRightClicked.connect(std::bind(&SceneState::slotCursorRightClicked, this, std::placeholders::_1));
	g_scene.getCursor().signalMoved.connect(std::bind(&SceneState::slotCursorMoved, this, std::placeholders::_1, std::placeholders::_2));
}

void SceneState::draw()
{
	g_scene.render();
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
		g_scene.handleEvent(event);

	return stopEventPropagation;
}

void SceneState::slotBackToMainMenu()
{
	_backToMainMenu = true;
}

} // namespace qrw
