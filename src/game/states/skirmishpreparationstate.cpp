#include "game/states/skirmishpreparationstate.hpp"

#include "gui/ng/confirmationdialog.hpp"
#include "gui/ng/messagedialog.hpp"

#include "eventsystem/inputevents.hpp"

#include "game/skirmish/mapmanager.hpp"
#include "game/eventhandlerpriority.hpp"

namespace qrw
{

SkirmishPreparationState::SkirmishPreparationState(sf::RenderWindow* renderWindow, MapManager& mapManager, const SkirmishGuiFactory& guiFactory)
	: GameState(renderWindow, EGSID_SKIRMISH_PREPARATION_STATE),
	  EventHandler(EventHandlerPriority::DEFAULT),
	  mapManager_(mapManager),
	  nextState_(EGSID_NO_CHANGE)
{
	skirmishPreparationWindow_ = guiFactory.createSkirmishPreparationGui();
	skirmishPreparationWindow_->setSize({(float)renderWindow->getSize().x, (float)renderWindow->getSize().y});
	skirmishPreparationWindow_->signalBeginSkirmishClicked.connect([this] { slotToSkirmishStateClicked(); });
	skirmishPreparationWindow_->setPlayerOneName("Player I.");
	skirmishPreparationWindow_->setPlayerTwoName("Player II.");
	_guiUptr->addWidget(skirmishPreparationWindow_);

	backToMainMenuDialog_ = new namelessgui::ConfirmationDialog("Really go back to main menu?");
	backToMainMenuDialog_->signalYesClicked.connect([this] { slotBackToMainMenuClicked(); });
	_guiUptr->addWidget(backToMainMenuDialog_);

	noMapsDialog_ = new namelessgui::MessageDialog();
	noMapsDialog_->setMessage("There are no maps available!\n\nTo create maps, choos the map editor from the main menu.");
	noMapsDialog_->setButtonText("Back to main menu");
	noMapsDialog_->signalClosed.connect([this] { slotBackToMainMenuClicked(); });
	noMapsDialog_->setAnchor({0.5f, 0.5f});
	noMapsDialog_->setParentAnchor({0.5f, 0.5f});
	noMapsDialog_->setSize({300.0f, 250.0f});
	_guiUptr->addWidget(noMapsDialog_);

	_guiUptr->setVisible(true);

	backToMainMenuDialog_->setVisible(false);
	noMapsDialog_->setVisible(false);
}

EGameStateId SkirmishPreparationState::update()
{
	return nextState_;
}

void SkirmishPreparationState::draw()
{
	_guiUptr->render(*_renderWindow, sf::RenderStates::Default);
}

bool SkirmishPreparationState::handleEvent(const IEvent& event)
{
	if(event.getName() == KeyPressedEvent::name)
	{
		if(static_cast<const KeyPressedEvent&>(event).key == KeyboardKey::Esc)
		{
			backToMainMenuDialog_->setVisible(true);
			return true;
		}
	}

	return false;
}

const std::string& SkirmishPreparationState::getPlayerOneName() const
{
	return skirmishPreparationWindow_->getPlayerOneName();
}

const std::string& SkirmishPreparationState::getPlayerTwoName() const
{
	return skirmishPreparationWindow_->getPlayerTwoName();
}

const std::string& SkirmishPreparationState::getMapName() const
{
	return skirmishPreparationWindow_->getSelectedMapName();
}

void SkirmishPreparationState::init(GameState* previousState)
{
	GameState::init(previousState);

	if(mapManager_.getMapList().empty())
	{
		skirmishPreparationWindow_->setVisible(false);
		noMapsDialog_->setVisible(true);
	}
}

} // namespace qrw
