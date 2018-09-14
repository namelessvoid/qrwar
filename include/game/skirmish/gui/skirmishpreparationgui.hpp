#ifndef QRW_SKIRMISHPREPARATIONGUI_HPP
#define QRW_SKIRMISHPREPARATIONGUI_HPP

#include "gui/ng/window.hpp"

namespace namelessgui
{
class LineInput;
class ListWidget;
}

namespace qrw
{
class SkirmishPreparationPlayerOptions;
class MapSelectionWindow;

class SkirmishPreparationGui : public namelessgui::Window
{
public:
	SkirmishPreparationGui();

	SkirmishPreparationGui(const SkirmishPreparationGui& rhs) = delete;

	void setSize(const sf::Vector2f& size) override;

	void setMaps(const std::vector<std::string>& mapNames);

	const std::string& getPlayerOneName() const;
	const std::string& getPlayerTwoName() const;

	const std::string& getSelectedMapName() const;

	namelessgui::Signal<> signalBeginSkirmishClicked;

private:
	MapSelectionWindow* mapSelectionWindow_;
	SkirmishPreparationPlayerOptions* playerOneOptions_;
	SkirmishPreparationPlayerOptions* playerTwoOptions_;
};

} // namespace qrw

#endif // QRW_SKIRMISHPREPARATIONGUI_HPP