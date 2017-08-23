#include "game/states/scenestate.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "config/settings.hpp"
#include "eventsystem/event.hpp"
#include "game/events.hpp"
#include "gui/cursor.hpp"

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
}

void SceneState::draw()
{
	_guiUptr->render(*_renderWindow, sf::RenderStates::Default);
}

bool SceneState::handleEvent(sf::Event& event)
{
	bool stopEventPropagation = GameState::handleEvent(event);

	if(event.type == sf::Event::KeyPressed)
		if(event.key.code == sf::Keyboard::Escape)
			_backToMainMenuDialog->setVisible(true);

	return stopEventPropagation;
}

bool SceneState::handleEvent(const Event &event)
{
	if(event.name == SID("CURSOR_MOVED"))
	{
		slotCursorMoved(static_cast<const CursorMovedEvent&>(event).coordinates);
	}
	else if(event.name == SID("CURSOR_LEFT_CLICKED"))
	{
		slotCursorLeftClicked(static_cast<const CursorLeftClickedEvent&>(event).coordinates);
	}
	else if (event.name == SID("CURSOR_RIGHT_CLICKED"))
	{
		slotCursorRightClicked(static_cast<const CursorRightClickedEvent&>(event).coordinates);
	}
	return false;
}

void SceneState::slotBackToMainMenu()
{
	_backToMainMenu = true;
}

} // namespace qrw
