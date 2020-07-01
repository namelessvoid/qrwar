#ifndef QRW_MAPSELECTIONWINDOW_HPP
#define QRW_MAPSELECTIONWINDOW_HPP

#include "gui/ng/window.hpp"
#include "mappreview.hpp"

namespace namelessgui
{
class ListWidget;
}

namespace qrw
{
class MapManager;

class MapSelectionWindow : public namelessgui::Window
{
public:
	void setSize(const sf::Vector2f& size) override;

	explicit MapSelectionWindow(MapManager& mapManager);

	MapSelectionWindow(MapSelectionWindow& rhs) = delete;
	MapSelectionWindow& operator=(MapSelectionWindow& rhs) = delete;

	const std::string& getSelectedMapName() const;

private:
	void slotMapSelectionChanged(const std::string& mapName);

	namelessgui::ListWidget* mapNameList_;
	MapPreview* mapPreview_;
	sf::Vector2f maxMapPreviewSize_;

	std::string selectedMapName_;

	MapManager& mapManager_;
};

}

#endif //QRW_MAPSELECTIONWINDOW_HPP
