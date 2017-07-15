#include "gui/squaredetailwindow.hpp"

#include "gui/ng/label.hpp"

#include "gui/texturemanager.hpp"
#include "gui/guihelper.hpp"

#include "engine/square.hpp"

namespace qrw
{

SquareDetailWindow::SquareDetailWindow()
{
    setSize({400.0f, 150.0f});
    setAnchor({0.0f, 1.0f});
    setParentAnchor({0.0f, 1.0f});

    float labelHeight = 50;

    // ------------------
    // Labels for displaying unit information
    // ------------------
    namelessgui::Label* label;
    label = new namelessgui::Label();
    label->setSize({100, labelHeight});
    label->setText("Unit name");
    label->setImage(TextureManager::getInstance()->getTexture("p1swordman"));
    label->setRelativePosition({0, 0});
    _unitTitleLabel = label;
    addWidget(_unitTitleLabel);

    label = new namelessgui::Label();
    label->setSize({100, labelHeight});
    label->setText("20 / 100 HP");
    label->setImage(TextureManager::getInstance()->getTexture("health"));
    label->setRelativePosition({0, labelHeight});
    _unitHealthLabel = label;
    addWidget(_unitHealthLabel);

	label = new namelessgui::Label();
	label->setSize({100, labelHeight});
	label->setText("movement");
	label->setImage(TextureManager::getInstance()->getTexture("movement"));
	label->setRelativePosition({150, labelHeight});
	_unitMovementLabel = label;
	addWidget(_unitMovementLabel);

    label = new namelessgui::Label();
    label->setSize({100, labelHeight});
    label->setText("3");
    label->setImage(TextureManager::getInstance()->getTexture("attack"));
    label->setRelativePosition({0, 2 * labelHeight});
    _unitAttackLabel = label;
    addWidget(_unitAttackLabel);

    label = new namelessgui::Label();
    label->setSize({100, labelHeight});
    label->setText("2");
    label->setImage(TextureManager::getInstance()->getTexture("defense"));
	label->setRelativePosition({150, 2 * labelHeight});
    _unitDefenseLabel = label;
    addWidget(_unitDefenseLabel);

    // ------------------
    // Labels for displaying terrain information
    // ------------------
    label = new namelessgui::Label();
    label->setSize({100, labelHeight});
    label->setText("Wall");
    label->setImage(TextureManager::getInstance()->getTexture("wall"));
    label->setParentAnchor({1, 0});
    label->setRelativePosition({-200, 0});
    _terrainTitleLabel = label;
    addWidget(_terrainTitleLabel);

    label = new namelessgui::Label();
    label->setSize({100, labelHeight});
    label->setText("+1");
    label->setImage(TextureManager::getInstance()->getTexture("attack"));
    label->setParentAnchor({1, 0});
    label->setRelativePosition({-200, labelHeight});
    _terrainAttackLabel = label;
    addWidget(_terrainAttackLabel);

    label = new namelessgui::Label();
    label->setSize({100, labelHeight});
    label->setText("-1");
    label->setImage(TextureManager::getInstance()->getTexture("defense"));
    label->setParentAnchor({1, 0});
    label->setRelativePosition({-100, labelHeight});
    _terrainDefenseLabel = label;
    addWidget(_terrainDefenseLabel);
}

void SquareDetailWindow::setSquare(Square *square)
{
    if(square)
    {
        // Hide window if there's nothing to display
        if(square->getUnit() == nullptr && square->getTerrain() == nullptr)
            setVisible(false);
        else
            setVisible(true);

        setUnit(square->getUnit());
        setTerrain(square->getTerrain());
    }
    else
        setVisible(false);
}

void SquareDetailWindow::setUnit(Unit::Ptr unit)
{
    if(unit)
    {
        _unitTitleLabel->setVisible(true);
		_unitTitleLabel->setImage(unit->getTexture());
        _unitTitleLabel->setText(GuiHelper::getUnitName(unit));

        _unitHealthLabel->setVisible(true);
		_unitHealthLabel->setText(std::to_string(unit->getHP()) + "/" + std::to_string(unit->getMaxHp()));

		_unitMovementLabel->setVisible(true);
		_unitMovementLabel->setText(std::to_string(unit->getCurrentMovement()) + "/" + std::to_string(unit->getMovement()));

        _unitAttackLabel->setVisible(true);
        _unitAttackLabel->setText(std::to_string(unit->getBaseAttack()));

        _unitDefenseLabel->setVisible(true);
        _unitDefenseLabel->setText(std::to_string(unit->getBaseDefense()));
    }
    else
    {
        _unitTitleLabel->setVisible(false);
        _unitHealthLabel->setVisible(false);
		_unitMovementLabel->setVisible(false);
        _unitAttackLabel->setVisible(false);
        _unitDefenseLabel->setVisible(false);
    }
}

void SquareDetailWindow::setTerrain(Terrain::Ptr terrain)
{
    if(terrain)
    {
        _terrainTitleLabel->setVisible(true);
        _terrainTitleLabel->setImage(GuiHelper::getTerrainTexture(terrain));
        _terrainTitleLabel->setText(GuiHelper::getTerrainName(terrain));

        _terrainAttackLabel->setVisible(true);
        _terrainAttackLabel->setText(std::to_string(terrain->getModificator(MODIFICATORS::EM_ATTACK)));

        _terrainDefenseLabel->setVisible(true);
        _terrainDefenseLabel->setText(std::to_string(terrain->getModificator(MODIFICATORS::EM_DEFENSE)));

    }
    else
    {
        _terrainTitleLabel->setVisible(false);
        _terrainAttackLabel->setVisible(false);
        _terrainDefenseLabel->setVisible(false);
    }
}

} // namespace qrw
