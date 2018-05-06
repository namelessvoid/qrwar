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

SkirmishPreparationState::SkirmishPreparationState(sf::RenderWindow* renderWindow)
	: GameState(renderWindow, EGSID_SKIRMISH_PREPARATION_STATE),
	  EventHandler(EventHandlerPriority::DEFAULT),
	  nextState_(EGSID_NO_CHANGE)
{
	namelessgui::Window* window = new namelessgui::Window();
	window->setSize({(float)renderWindow->getSize().x, (float)renderWindow->getSize().y});
	_guiUptr->addWidget(window);

	namelessgui::Button* toSkirmisStateButton = new namelessgui::Button();
	toSkirmisStateButton->signalClicked.connect(std::bind(&SkirmishPreparationState::slotToSkirmishStateClicked, this));
	toSkirmisStateButton->setText("Start Skirmish");
	toSkirmisStateButton->setSize({150, 30});
	toSkirmisStateButton->setAnchor({1, 1});
	toSkirmisStateButton->setParentAnchor({1, 1});
	toSkirmisStateButton->setRelativePosition({-5, -5});
	window->addWidget(toSkirmisStateButton);

	playerOneName_ = new namelessgui::LineInput();
	playerOneName_->setText("Sigurdson");
	playerOneName_->setSize({200, 30});
	playerOneName_->setRelativePosition({100, 200});
	window->addWidget(playerOneName_);

	playerTwoName_ = new namelessgui::LineInput();
	playerTwoName_->setText("King Karl XIII");
	playerTwoName_->setSize({200, 30});
	playerTwoName_->setRelativePosition({400, 200});
	window->addWidget(playerTwoName_);

	backToMainMenuDialog_ = new namelessgui::ConfirmationDialog("Really go back to main menu?");
	backToMainMenuDialog_->signalYesClicked.connect(std::bind(&SkirmishPreparationState::slotBackToMainMenuClicked, this));
	_guiUptr->addWidget(backToMainMenuDialog_);

	_guiUptr->setVisible(true);

	backToMainMenuDialog_->setVisible(false);

	// Init map list widget
	namelessgui::ListWidget* mapList = new namelessgui::ListWidget();
	mapList->signalItemSelected.connect([this] (const std::string& mapName) { slotMapSelected(mapName); });
	mapList->setSize({250, 100});
	mapList->setPosition({10, 300});
	window->addWidget(mapList);

	std::vector<std::string> mapNames = MapManager::get()->getMapList();
	for(auto& mapName : mapNames)
		mapList->addItem(mapName);
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
	return playerOneName_->getText();
}

const std::string& SkirmishPreparationState::getPlayerTwoName() const
{
	return playerTwoName_->getText();
}

} // namespace qrw
