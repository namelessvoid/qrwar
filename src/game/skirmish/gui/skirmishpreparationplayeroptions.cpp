#include "game/skirmish/gui/skirmishpreparationplayeroptions.hpp"

#include "gui/ng/lineinput.hpp"

namespace qrw
{

SkirmishPreparationPlayerOptions::SkirmishPreparationPlayerOptions()
{
	playerNameInput_ = new namelessgui::LineInput();
	playerNameInput_->setText("Player Name");
	playerNameInput_->setSize({200, 30});
	playerNameInput_->setRelativePosition({0, 0});
	addWidget(playerNameInput_);
}

const std::string& SkirmishPreparationPlayerOptions::getPlayerName()
{
	return playerNameInput_->getText();
}

void SkirmishPreparationPlayerOptions::setPlayerName(const std::string& name)
{
	{ playerNameInput_->setText(name); }
}

} //namespace qrw