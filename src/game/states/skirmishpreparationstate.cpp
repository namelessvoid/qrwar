#include "game/states/skirmishpreparationstate.hpp"

#include "gui/ng/window.hpp"
#include "gui/ng/button.hpp"

namespace qrw
{

SkirmishPreparationState::SkirmishPreparationState(sf::RenderWindow* renderWindow)
	: GameState(renderWindow, EGSID_SKIRMISH_PREPARATION_STATE),
	  toSkirmishState_(false)
{
	window_ = new namelessgui::Window();
	window_->setSize({(float)renderWindow->getSize().x, (float)renderWindow->getSize().y});

	namelessgui::Button* toSkirmisStateButton = new namelessgui::Button();
	toSkirmisStateButton->signalclicked.connect(std::bind(&SkirmishPreparationState::slotToSkirmishStateClicked, this));
	window_->addWidget(toSkirmisStateButton);

	_guiUptr->addWidget(window_);
	_guiUptr->setVisible(true);
}

SkirmishPreparationState::~SkirmishPreparationState()
{
}

EGameStateId SkirmishPreparationState::update()
{
	if(toSkirmishState_)
		return EGameStateId::EGSID_DEPLOY_STATE;

	return EGameStateId::EGSID_NO_CHANGE;
}

void SkirmishPreparationState::draw()
{
	_guiUptr->render(*_renderWindow, sf::RenderStates::Default);
}

void SkirmishPreparationState::slotToSkirmishStateClicked()
{
	toSkirmishState_ = true;
}

} // namespace qrw
