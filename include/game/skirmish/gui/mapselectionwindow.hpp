#ifndef QRW_MAPSELECTIONWINDOW_HPP
#define QRW_MAPSELECTIONWINDOW_HPP

#include "gui/ng/window.hpp"

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
	namelessgui::RectangularWidget* mapPreview_;

	std::string selectedMapName_;

	MapManager& mapManager_;
};

}

#endif //QRW_MAPSELECTIONWINDOW_HPP
