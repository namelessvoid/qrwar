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
	mapPreview_->setRotation(45.0f);
	mapPreview_->setSize(sf::Vector2f(texture->getSize().x, texture->getSize().y));

	updateMapPreviewSize();
}

void MapSelectionWindow::updateMapPreviewSize()
{
	if(mapPreview_->getTexture() == nullptr) return;
	mapPreview_->setScale(1, 1);

	sf::Vector2f sizeMapPreview = maxMapPreviewSize_;
	sf::FloatRect spriteBounds = mapPreview_->getGlobalBounds();
	float scale = 1;

	// Only resize if texture is valid and possible preview size is > zero
	if(spriteBounds.width != 0 && spriteBounds.height != 0 && maxMapPreviewSize_.x != 0 && maxMapPreviewSize_.y != 0)
	{
		float scaleX = maxMapPreviewSize_.x / spriteBounds.width;
		float scaleY = maxMapPreviewSize_.y / spriteBounds.height;
		scale = std::min(scaleX, scaleY);
	}

	mapPreview_->setScale(scale, scale);
}

} // namespace qrw