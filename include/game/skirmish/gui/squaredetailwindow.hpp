#ifndef QRW_SQUAREDETAILWINDOW_HPP
#define QRW_SQUAREDETAILWINDOW_HPP

#include "gui/ng/window.hpp"
#include "gui/ng/radiotogglebutton.hpp"
#include "gui/ng/buttongroup.hpp"

#include "game/skirmish/unitability.hpp"

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
	~SquareDetailWindow() override;

	void display(const Coordinates& position, Board& board, Player& currentPlayer);

	void clear();

	void deselectSelectedUnitAbility();
	inline UnitAbility* getSelectedUnitAbility() const { return selectedUnitAbility_; }

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
	std::vector<std::unique_ptr<namelessgui::RadioToggleButton>> unitAbilityButtons_;
	std::shared_ptr<namelessgui::ButtonGroup> unitAbilitiesButtonGroup_;

	namelessgui::Label* environmentTitleLabel_;
	namelessgui::Label* environmentAttackLabel_;
	namelessgui::Label* environmentDefenseLabel_;

	UnitAbility* selectedUnitAbility_;
};

} // namespace qrw

#endif // QRW_SQUAREDETAILWINDOW_HPP
