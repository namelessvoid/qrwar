#ifndef QRW_SQUAREDETAILWINDOW_HPP
#define QRW_SQUAREDETAILWINDOW_HPP

#include "gui/ng/window.hpp"
#include "gui/ng/radiotogglebutton.hpp"
#include "gui/ng/buttongroup.hpp"

#include "game/skirmish/unitspecialability.hpp"

namespace namelessgui
{
class Label;
}

namespace qrw
{
class Coordinates;
class Board;
class Player;
class Unit;
class Terrain;
class Structure;

class SquareDetailWindow : public namelessgui::Window
{
public:
	SquareDetailWindow();

	void display(const Coordinates& position, Board& board, Player& currentPlayer);

	void clear();

	void deselectSelectedUnitSpecialAbility();
	inline UnitSpecialAbility* getSelectedUnitSpecialAbility() const { return selectedUnitSpecialAbility_; }

private:
	void setUnit(const Unit& unit);
	void showUnitSpecialAbilities(const Unit& unit);
	void clearUnitSpecialAbilities();
	void hideUnitWidgets();

	void setTerrain(const Terrain& terrain);
	void setStructure(const Structure& structure);
	void hideEnvironmentWidgets();

	namelessgui::Label* unitTitleLabel_;
	namelessgui::Label* unitHealthLabel_;
	namelessgui::Label* unitMovementLabel_;
	namelessgui::Label* unitAttackLabel_;
	namelessgui::Label* unitDefenseLabel_;
	std::vector<std::unique_ptr<namelessgui::RadioToggleButton>> unitSpecialAbilityButtons_;
	std::shared_ptr<namelessgui::ButtonGroup> unitSpecialAbilitiesButtonGroup_;

	namelessgui::Label* environmentTitleLabel_;
	namelessgui::Label* environmentAttackLabel_;
	namelessgui::Label* environmentDefenseLabel_;

	UnitSpecialAbility* selectedUnitSpecialAbility_;
};

} // namespace qrw

#endif // QRW_SQUAREDETAILWINDOW_HPP
