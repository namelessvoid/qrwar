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
	mapPreview_->setAnchor({0, 0});
	mapPreview_->setParentAnchor({0.4, 0});
	mapPreview_->setRelativePosition({5, 5});
	mapPreview_->setVisible(true);
	addWidget(mapPreview_);

	// Initialize map list
	auto mapNames = mapManager_.getMapList();
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

	maxMapPreviewSize_ = {size.x * 0.6f - 10.0f, size.y - 10.0f};
	updateMapPreviewSize();
}

void MapSelectionWindow::slotMapSelectionChanged(const std::string& mapName)
{
	selectedMapName_ = mapName;

	sf::Texture* texture = mapManager_.loadMapPreview(selectedMapName_);
	mapPreview_->setTexture(texture);

	updateMapPreviewSize();
}

void MapSelectionWindow::updateMapPreviewSize()
{
	if(mapPreview_->getTexture() == nullptr) return;

	sf::Vector2f sizeMapPreview = maxMapPreviewSize_;
	sf::Vector2f sizeTexture(mapPreview_->getTexture()->getSize().x, mapPreview_->getTexture()->getSize().y);

	// Only resize if texture is valid and possible preview size is > zero
	if(sizeTexture.x != 0 && sizeTexture.y != 0 && maxMapPreviewSize_.x != 0 && maxMapPreviewSize_.y != 0)
	{
		float aspectRatioTexture = sizeTexture.x / sizeTexture.y;
		float aspectRatioMapPreview = maxMapPreviewSize_.x / maxMapPreviewSize_.y;

		if(aspectRatioTexture < aspectRatioMapPreview)
			sizeMapPreview.x = maxMapPreviewSize_.y * aspectRatioTexture;
		else if(aspectRatioTexture > aspectRatioMapPreview)
			sizeMapPreview.y = maxMapPreviewSize_.x / aspectRatioTexture;
	}

	mapPreview_->setSize(sizeMapPreview);
}

} // namespace qrw