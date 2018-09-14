#ifndef QRW_MAPSELECTIONWINDOW_HPP
#define QRW_MAPSELECTIONWINDOW_HPP

#include "gui/ng/window.hpp"

namespace namelessgui
{
class ListWidget;
}

namespace qrw
{

class MapSelectionWindow : public namelessgui::Window
{
public:
	void setSize(const sf::Vector2f& size) override;

	MapSelectionWindow();

	MapSelectionWindow(MapSelectionWindow& rhs) = delete;
	MapSelectionWindow& operator=(MapSelectionWindow& rhs) = delete;

	void setMaps(const std::vector<std::string>& mapNames);
	const std::string& getSelectedMapName() const;

private:
	namelessgui::ListWidget* mapNameList_;
	std::string selectedMapName_;
};

}

#endif //QRW_MAPSELECTIONWINDOW_HPP
