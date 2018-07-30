#ifndef QRW_MAPEDITORTOOLBAR_HPP
#define QRW_MAPEDITORTOOLBAR_HPP

#include "gui/ng/tabwidget.hpp"

#include "engine/terraintypes.hpp"

namespace namelessgui
{
class Window;
class LineInput;
}

namespace qrw
{

class MapEditorToolBar : public namelessgui::TabWidget
{
public:
	MapEditorToolBar(unsigned int initialBoardWidth, unsigned int initialBoardHeight);

	~MapEditorToolBar() override = default;

	namelessgui::Signal<const std::string> signalSaveClicked;
	namelessgui::Signal<const std::string> signalLoadClicked;

	namelessgui::Signal<unsigned int> signalBoardWidthChanged;
	namelessgui::Signal<unsigned int> signalBoardHeightChanged;

	namelessgui::Signal<TERRAINTYPES> signalTerrainTypeClicked;
	namelessgui::Signal<> signalEraseTerrainClicked;
	namelessgui::Signal<unsigned int> signalDeploymentZoneClicked;
	namelessgui::Signal<> signalEraseDeploymentZoneClicked;

private:
	namelessgui::Window* createConfigToolsWindow(unsigned int initialBoardWidth, unsigned int initialBoardHeight);
	namelessgui::Window* createTerrainToolsWindow();
	namelessgui::Window* createStructureToolsWindow();
	namelessgui::Window* createDeploymentZoneToolsWindow();

	namelessgui::LineInput* mapNameInput_;

	const sf::Vector2f BUTTON_SIZE = sf::Vector2f(140.0f, 50.0f);
	const float BUTTON_Y_OFFSET = 45;
};

} // namespace qrw


#endif //QRW_MAPEDITORTOOLBAR_HPP
