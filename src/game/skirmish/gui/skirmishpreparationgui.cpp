#include "game/skirmish/gui/skirmishpreparationgui.hpp"

#include "gui/ng/button.hpp"
#include "gui/ng/lineinput.hpp"
#include "gui/ng/listwidget.hpp"

#include "game/skirmish/gui/skirmishguifactory.hpp"
#include "game/skirmish/gui/mapselectionwindow.hpp"
#include "game/skirmish/gui/skirmishpreparationplayeroptions.hpp"

namespace qrw
{

SkirmishPreparationGui::SkirmishPreparationGui(const SkirmishGuiFactory& skirmishGuiFactory)
{
	namelessgui::Button* toSkirmisStateButton = new namelessgui::Button();
	toSkirmisStateButton->signalClicked.connect([this] { signalBeginSkirmishClicked.emit(); });
	toSkirmisStateButton->setText("Start Skirmish");
	toSkirmisStateButton->setSize({150, 30});
	toSkirmisStateButton->setAnchor({1, 1});
	toSkirmisStateButton->setParentAnchor({1, 1});
	toSkirmisStateButton->setRelativePosition({-5, -5});
	addWidget(toSkirmisStateButton);

	mapSelectionWindow_ = skirmishGuiFactory.createMapSelectionWindow();
	mapSelectionWindow_->setRelativePosition({5, 5});
	addWidget(mapSelectionWindow_);

	playerOneOptions_ = new SkirmishPreparationPlayerOptions();
	playerOneOptions_->setAnchor({0, 1});
	playerOneOptions_->setParentAnchor({0, 1});
	playerOneOptions_->setRelativePosition({5, -40});
	addWidget(playerOneOptions_);

	playerTwoOptions_ = new SkirmishPreparationPlayerOptions();
	playerTwoOptions_->setAnchor({1, 1});
	playerTwoOptions_->setParentAnchor({1, 1});
	playerTwoOptions_->setRelativePosition({-5, -40});
	addWidget(playerTwoOptions_);
}

const std::string& SkirmishPreparationGui::getPlayerOneName() const
{
	return playerOneOptions_->getPlayerName();
}

const std::string& SkirmishPreparationGui::getPlayerTwoName() const
{
	return playerTwoOptions_->getPlayerName();
}

void SkirmishPreparationGui::setMaps(const std::vector<std::string>& mapNames)
{
	mapSelectionWindow_->setMaps(mapNames);
}

void SkirmishPreparationGui::setSize(const sf::Vector2f& size)
{
	RectangularWidget::setSize(size);
	mapSelectionWindow_->setSize({size.x - 10, 0.5f * size.y - 45});
	playerOneOptions_->setSize(0.5f * size);
	playerTwoOptions_->setSize(0.5f * size);
}

const std::string& SkirmishPreparationGui::getSelectedMapName() const
{
	return mapSelectionWindow_->getSelectedMapName();
}

} // namespace qrw
