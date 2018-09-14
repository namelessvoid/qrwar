#include "game/skirmish/gui/skirmishpreparationplayeroptions.hpp"

#include "gui/ng/lineinput.hpp"

qrw::SkirmishPreparationPlayerOptions::SkirmishPreparationPlayerOptions()
{
	playerNameInput_ = new namelessgui::LineInput();
	playerNameInput_->setText("Player I.");
	playerNameInput_->setSize({200, 30});
	playerNameInput_->setRelativePosition({0, 0});
	addWidget(playerNameInput_);
}

const std::string& qrw::SkirmishPreparationPlayerOptions::getPlayerName()
{
	return playerNameInput_->getText();
}
