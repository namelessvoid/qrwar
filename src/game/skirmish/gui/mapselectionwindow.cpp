#include "game/skirmish/gui/mapselectionwindow.hpp"

#include "gui/ng/listwidget.hpp"

#include "game/skirmish/mapmanager.hpp"

namespace qrw
{

MapSelectionWindow::MapSelectionWindow(MapManager& mapManager)
	: mapManager_(mapManager)
{
	mapNameList_ = new namelessgui::ListWidget();
	mapNameList_->signalItemSelected.connect([this] (const std::string& mapName) { slotMapSelectionChanged(mapName); });
	mapNameList_->setPosition({0, 0});
	addWidget(mapNameList_);

	mapPreview_ = new namelessgui::RectangularWidget();
	mapPreview_->setFillColor(sf::Color::White);
	mapPreview_->setAnchor({1, 0});
	mapPreview_->setParentAnchor({1, 0});
	mapPreview_->setRelativePosition({-5, 5});
	mapPreview_->setVisible(true);
	addWidget(mapPreview_);
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
	mapNameList_->setSize({size.x * 0.4f, size.y - 5.0f});
	mapPreview_->setSize({size.x * 0.6f - 10.0f, size.y - 10.0f});
}

void MapSelectionWindow::slotMapSelectionChanged(const std::string& mapName)
{
	selectedMapName_ = mapName;

	sf::Texture* texture = mapManager_.loadMapPreview(selectedMapName_);
	mapPreview_->setTexture(texture);
}

} // namespace qrw