#ifndef QRW_SQUAREDETAILWINDOW_HPP
#define QRW_SQUAREDETAILWINDOW_HPP

#include "gui/ng/window.hpp"

namespace namelessgui
{
class Label;
}

namespace qrw
{
class Coordinates;
class Board;
class Unit;
class Terrain;
class Structure;

class SquareDetailWindow : public namelessgui::Window
{
public:
	SquareDetailWindow();

	void display(const Coordinates& position, Board& board);

private:
	void setUnit(const Unit& unit);
	void hideUnitWidgets();

	void setTerrain(const Terrain& terrain);
	void setStructure(const Structure& structure);
	void hideEnvironmentWidgets();

	namelessgui::Label* unitTitleLabel_;
	namelessgui::Label* unitHealthLabel_;
	namelessgui::Label* unitMovementLabel_;
	namelessgui::Label* unitAttackLabel_;
	namelessgui::Label* unitDefenseLabel_;

	namelessgui::Label* environmentTitleLabel_;
	namelessgui::Label* environmentAttackLabel_;
	namelessgui::Label* environmentDefenseLabel_;
};

} // namespace qrw

#endif // QRW_SQUAREDETAILWINDOW_HPP
