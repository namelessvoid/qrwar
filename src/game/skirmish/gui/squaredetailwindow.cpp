#include "game/skirmish/gui/squaredetailwindow.hpp"

#include "gui/ng/label.hpp"

#include "gui/texturemanager.hpp"
#include "gui/guihelper.hpp"

#include "engine/player.hpp"
#include "game/skirmish/unit.hpp"
#include "engine/terrain.hpp"
#include "game/skirmish/structure.hpp"
#include "game/skirmish/wall.hpp"

namespace qrw
{

SquareDetailWindow::SquareDetailWindow()
	: selectedUnitAbility_(nullptr)
{
    setSize({800.0f, 150.0f});
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
    unitTitleLabel_ = label;
    addWidget(unitTitleLabel_);

    label = new namelessgui::Label();
    label->setSize({100, labelHeight});
    label->setText("20 / 100 HP");
    label->setImage(TextureManager::getInstance()->getTexture("health"));
    label->setRelativePosition({0, labelHeight});
    unitHealthLabel_ = label;
    addWidget(unitHealthLabel_);

	label = new namelessgui::Label();
	label->setSize({100, labelHeight});
	label->setText("movement");
	label->setImage(TextureManager::getInstance()->getTexture("movement"));
	label->setRelativePosition({100, labelHeight});
	unitMovementLabel_ = label;
	addWidget(unitMovementLabel_);

    label = new namelessgui::Label();
    label->setSize({100, labelHeight});
    label->setText("3");
    label->setImage(TextureManager::getInstance()->getTexture("attack"));
    label->setRelativePosition({0, 2 * labelHeight});
    unitAttackLabel_ = label;
    addWidget(unitAttackLabel_);

    label = new namelessgui::Label();
    label->setSize({100, labelHeight});
    label->setText("2");
    label->setImage(TextureManager::getInstance()->getTexture("defense"));
	label->setRelativePosition({100, 2 * labelHeight});
    unitDefenseLabel_ = label;
    addWidget(unitDefenseLabel_);

    // ------------------
    // Labels for displaying terrain information
    // ------------------
    label = new namelessgui::Label();
    label->setSize({100, labelHeight});
    label->setText("Wall");
    label->setImage(TextureManager::getInstance()->getTexture("wall"));
    label->setParentAnchor({1, 0});
    label->setRelativePosition({-200, 0});
    environmentTitleLabel_ = label;
    addWidget(environmentTitleLabel_);

    label = new namelessgui::Label();
    label->setSize({100, labelHeight});
    label->setText("+1");
    label->setImage(TextureManager::getInstance()->getTexture("attack"));
    label->setParentAnchor({1, 0});
    label->setRelativePosition({-200, labelHeight});
    environmentAttackLabel_ = label;
    addWidget(environmentAttackLabel_);

    label = new namelessgui::Label();
    label->setSize({100, labelHeight});
    label->setText("-1");
    label->setImage(TextureManager::getInstance()->getTexture("defense"));
    label->setParentAnchor({1, 0});
    label->setRelativePosition({-100, labelHeight});
    environmentDefenseLabel_ = label;
    addWidget(environmentDefenseLabel_);
}

SquareDetailWindow::~SquareDetailWindow()
{
	clearUnitSpecialAbilities();
}

void SquareDetailWindow::setUnit(const Unit& unit)
{
	unitTitleLabel_->setVisible(true);
	unitTitleLabel_->setImage(GuiHelper::getUnitTexture(unit.getType(), unit.getPlayer()->getId()));
	unitTitleLabel_->setText(GuiHelper::getUnitName(unit.getType()));

	unitHealthLabel_->setVisible(true);
	unitHealthLabel_->setText(std::to_string(unit.getHP()) + "/" + std::to_string(unit.getMaxHp()));

	unitMovementLabel_->setVisible(true);
	unitMovementLabel_->setText(std::to_string(unit.getCurrentMovement()) + "/" + std::to_string(unit.getMovement()));

	unitAttackLabel_->setVisible(true);
	unitAttackLabel_->setText(std::to_string(unit.getBaseAttack()));

	unitDefenseLabel_->setVisible(true);
	unitDefenseLabel_->setText(std::to_string(unit.getBaseDefense()));
}

void SquareDetailWindow::showUnitSpecialAbilities(const Unit& unit)
{
	clearUnitSpecialAbilities();
	unitAbilitiesButtonGroup_ = std::make_shared<namelessgui::ButtonGroup>();
	for(auto& ability : unit.getAbilities())
	{
		namelessgui::RadioToggleButton* abilityButton = new namelessgui::RadioToggleButton(unitAbilitiesButtonGroup_);
		abilityButton->setRelativePosition({200.0f, 50 + abilityButton->getSize().y * unitAbilityButtons_.size()});
		abilityButton->setText(ability->getName());
		addWidget(abilityButton);

		unitAbilityButtons_.push_back(nullptr);
		unitAbilityButtons_.back().reset(abilityButton);
		abilityButton->signalActivated.connect([this,ability] { selectedUnitAbility_ = ability; });
	}
}

void SquareDetailWindow::hideUnitWidgets()
{
	unitTitleLabel_->setVisible(false);
	unitHealthLabel_->setVisible(false);
	unitMovementLabel_->setVisible(false);
	unitAttackLabel_->setVisible(false);
	unitDefenseLabel_->setVisible(false);
	clearUnitSpecialAbilities();
}

void SquareDetailWindow::setTerrain(const Terrain& terrain)
{
	environmentTitleLabel_->setVisible(true);
	environmentTitleLabel_->setImage(GuiHelper::getTerrainTexture(terrain.getType()));
	environmentTitleLabel_->setText(GuiHelper::getTerrainName(&terrain));

	environmentAttackLabel_->setVisible(true);
	environmentAttackLabel_->setText(std::to_string(terrain.getModificator(MODIFICATORS::EM_ATTACK)));

	environmentDefenseLabel_->setVisible(true);
	environmentDefenseLabel_->setText(std::to_string(terrain.getModificator(MODIFICATORS::EM_DEFENSE)));
}

void SquareDetailWindow::setStructure(const Structure& structure)
{
	std::string text = dynamic_cast<const Wall*>(&structure) != nullptr ? "Wall" : "Stairs";
	environmentTitleLabel_->setText(text);
	environmentTitleLabel_->setImage(structure.getTexture());
	environmentTitleLabel_->setVisible(true);

	environmentAttackLabel_->setVisible(false);
	environmentDefenseLabel_->setVisible(false);
}

void SquareDetailWindow::hideEnvironmentWidgets()
{
	environmentTitleLabel_->setVisible(false);
	environmentAttackLabel_->setVisible(false);
	environmentDefenseLabel_->setVisible(false);
}

void SquareDetailWindow::display(const Coordinates& position, Board& board, Player& currentPlayer)
{
	if(Unit* unit = board.getUnit(position))
	{
		setUnit(*unit);
		if(*unit->getPlayer() == currentPlayer) showUnitSpecialAbilities(*unit);
		else clearUnitSpecialAbilities();
	}
	else
		hideUnitWidgets();

	if(Terrain* terrain = board.getTerrain(position))
		setTerrain(*terrain);
	else if(Structure* structure = board.getStructure(position))
		setStructure(*structure);
	else
		hideEnvironmentWidgets();
}

void SquareDetailWindow::clearUnitSpecialAbilities()
{
	selectedUnitAbility_ = nullptr;
	for(auto& abilityButton : unitAbilityButtons_)
		removeWidget(abilityButton.get());
	unitAbilityButtons_.clear();
	unitAbilitiesButtonGroup_.reset();
}

void SquareDetailWindow::clear()
{
	hideUnitWidgets();
	clearUnitSpecialAbilities();
	hideEnvironmentWidgets();
}

void SquareDetailWindow::deselectSelectedUnitAbility()
{
	selectedUnitAbility_ = nullptr;
	for(auto& button : unitAbilityButtons_)
		button->deactivate();
}

} // namespace qrw
