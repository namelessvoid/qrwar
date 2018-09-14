#include "game/skirmish/gui/mapselectionwindow.hpp"

#include "gui/ng/listwidget.hpp"

namespace qrw
{

MapSelectionWindow::MapSelectionWindow()
{
	mapNameList_ = new namelessgui::ListWidget();
	mapNameList_->signalItemSelected.connect([this] (const std::string& mapName) { selectedMapName_ = mapName; });
	mapNameList_->setSize(getSize());
	mapNameList_->setPosition({0, 0});
	addWidget(mapNameList_);
}

void MapSelectionWindow::setMaps(const std::vector<std::string>& mapNames)
{
	for(auto& mapName : mapNames)
		mapNameList_->addItem(mapName);
}

const std::string& MapSelectionWindow::getSelectedMapName() const
{
	return selectedMapName_;
}

void MapSelectionWindow::setSize(const sf::Vector2f& size)
{
	RectangularWidget::setSize(size);
	mapNameList_->setSize(size);
}

} // namespace qrw