#include "game/states/skirmishpreparationstate.hpp"

#include "gui/ng/window.hpp"
#include "gui/ng/button.hpp"
#include "gui/ng/lineinput.hpp"
#include "gui/ng/confirmationdialog.hpp"
#include "gui/ng/listwidget.hpp"

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
	_guiUptr->addWidget(skirmishPreparationWindow_);

	backToMainMenuDialog_ = new namelessgui::ConfirmationDialog("Really go back to main menu?");
	backToMainMenuDialog_->signalYesClicked.connect(std::bind(&SkirmishPreparationState::slotBackToMainMenuClicked, this));
	_guiUptr->addWidget(backToMainMenuDialog_);

	_guiUptr->setVisible(true);

	backToMainMenuDialog_->setVisible(false);

	// Init map list widget
	std::vector<std::string> mapNames = mapManager_.getMapList();
	skirmishPreparationWindow_->setMaps(mapNames);
}

SkirmishPreparationState::~SkirmishPreparationState()
{
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

} // namespace qrw
