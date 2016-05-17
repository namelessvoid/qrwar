#ifndef QRW_SQUAREDETAILWINDOW_HPP
#define QRW_SQUAREDETAILWINDOW_HPP

#include "gui/ng/window.hpp"

#include "engine/unit.hpp"
#include "engine/terrain.hpp"

namespace namelessgui
{
class Label;
}

namespace qrw
{

/**
 * @brief The SquareDetailWindow displays details about a square in the UI.
 *
 * It holds images and stats of the unit and terrain placed on a specific square.
 */
class SquareDetailWindow : public namelessgui::Window
{
public:
    SquareDetailWindow();

    void setSquare(class Square* square);

private:
    void setUnit(Unit::Ptr unit);
    void setTerrain(Terrain::Ptr terrain);

    namelessgui::Label* _unitTitleLabel;
    namelessgui::Label* _unitHealthLabel;
    namelessgui::Label* _unitAttackLabel;
    namelessgui::Label* _unitDefenseLabel;

    namelessgui::Label* _terrainTitleLabel;
    namelessgui::Label* _terrainAttackLabel;
    namelessgui::Label* _terrainDefenseLabel;
};

} // namespace qrw

#endif // QRW_SQUAREDETAILWINDOW_HPP
