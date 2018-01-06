#include "game/states/scenestate.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "config/settings.hpp"
#include "eventsystem/event.hpp"
#include "eventsystem/inputevents.hpp"
#include "game/events.hpp"
#include "gui/cursor.hpp"

namespace qrw
{

SceneState::SceneState(sf::RenderWindow* renderWindow, qrw::EGameStateId gameStateId)
	: GameState(renderWindow, gameStateId),
	  _backToMainMenu(false)
{
	// Initialize toolbar
	_toolBar = new namelessgui::Window();
	_toolBar->setSize({200.0f, (float)Settings::getInstance()->getResolutionY()});
	_toolBar->setAnchor({1.0f, 0.0f});
	_toolBar->setParentAnchor({1.0f, 0.0f});
	_guiUptr->addWidget(_toolBar);

	_guiUptr->setVisible(true);

	// Set up back to main menu dialog
	_backToMainMenuDialog = new namelessgui::ConfirmationDialog("Really exit and go back to main menu?");
	_backToMainMenuDialog->signalYesClicked.connect(std::bind(&SceneState::slotBackToMainMenu, this));
	_guiUptr->addWidget(_backToMainMenuDialog);
	_backToMainMenuDialog->setVisible(false);
}

SceneState::~SceneState()
{
}

void SceneState::init(GameState* previousState)
{
}

void SceneState::draw()
{
	_guiUptr->render(*_renderWindow, sf::RenderStates::Default);
}

bool SceneState::handleEvent(const IEvent &event)
{
	if(event.getName() == CursorMovedEvent::name)
	{
		slotCursorMoved(static_cast<const CursorMovedEvent&>(event).coordinates);
	}
	else if(event.getName() == CursorLeftClickedEvent::name)
	{
		slotCursorLeftClicked(static_cast<const CursorLeftClickedEvent&>(event).coordinates);
	}
	else if(event.getName() == CursorRightClickedEvent::name)
	{
		slotCursorRightClicked(static_cast<const CursorRightClickedEvent&>(event).coordinates);
	}
	else if(event.getName() == KeyPressedEvent::name)
	{
		if(static_cast<const KeyPressedEvent&>(event).key == KeyPressedEvent::Key::Esc)
			_backToMainMenuDialog->setVisible(true);
	}
	return false;
}

void SceneState::slotBackToMainMenu()
{
	_backToMainMenu = true;
}

} // namespace qrw
