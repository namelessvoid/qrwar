#include "game/states/skirmishpreparationstate.hpp"

#include "gui/ng/window.hpp"
#include "gui/ng/button.hpp"
#include "gui/ng/confirmationdialog.hpp"

#include "eventsystem/inputevents.hpp"

namespace qrw
{

SkirmishPreparationState::SkirmishPreparationState(sf::RenderWindow* renderWindow)
	: GameState(renderWindow, EGSID_SKIRMISH_PREPARATION_STATE),
	  nextState_(EGSID_NO_CHANGE)
{
	namelessgui::Window* window = new namelessgui::Window();
	window->setSize({(float)renderWindow->getSize().x, (float)renderWindow->getSize().y});
	_guiUptr->addWidget(window);

	namelessgui::Button* toSkirmisStateButton = new namelessgui::Button();
	toSkirmisStateButton->signalclicked.connect(std::bind(&SkirmishPreparationState::slotToSkirmishStateClicked, this));
	toSkirmisStateButton->setText("Start Skirmish");
	toSkirmisStateButton->setSize({150, 30});
	toSkirmisStateButton->setAnchor({1, 1});
	toSkirmisStateButton->setParentAnchor({1, 1});
	toSkirmisStateButton->setRelativePosition({-5, -5});
	window->addWidget(toSkirmisStateButton);

	backToMainMenuDialog_ = new namelessgui::ConfirmationDialog("Really go back to main menu?");
	backToMainMenuDialog_->signalYesClicked.connect(std::bind(&SkirmishPreparationState::slotBackToMainMenuClicked, this));
	_guiUptr->addWidget(backToMainMenuDialog_);

	_guiUptr->setVisible(true);

	backToMainMenuDialog_->setVisible(false);
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
		if(static_cast<const KeyPressedEvent&>(event).key == KeyPressedEvent::Key::Esc)
		{
			backToMainMenuDialog_->setVisible(true);
			return true;
		}
	}

	return false;
}

} // namespace qrw
