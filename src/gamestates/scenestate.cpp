#include "gamestates/scenestate.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "config/settings.hpp"

namespace qrw
{

SceneState::SceneState(sf::RenderWindow* renderWindow, qrw::EGameStateId gameStateId)
	: GameState(renderWindow, gameStateId),
	  _scene(nullptr)
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

    // Set up scene and scene signals
    _scene = std::unique_ptr<Scene>(new Scene(_renderWindow));
    _scene->signalCursorLeftClicked.connect(std::bind(&SceneState::slotCursorLeftClicked, this, std::placeholders::_1));
    _scene->signalCursorRightClicked.connect(std::bind(&SceneState::slotCursorRightClicked, this, std::placeholders::_1));
    _scene->signalCursorMoved.connect(std::bind(&SceneState::slotCursorMoved, this, std::placeholders::_1, std::placeholders::_2));
}

SceneState::~SceneState()
{
}

void SceneState::init(GameState* previousState)
{
	_backToMainMenu = false;
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
