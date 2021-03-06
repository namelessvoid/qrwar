#include "game/states/deploystate.hpp"

#include <memory>
#include <cassert>

#include "game/skirmish/unitfactory.hpp"
#include "game/skirmish/boardbackgroundcomponent.hpp"
#include "engine/terrain.hpp"
#include "game/skirmish/structure.hpp"

#include "foundation/spritecomponent.hpp"

#include "game/states/skirmishpreparationstate.hpp"
#include "game/cameras/skirmishcamera.hpp"
#include "game/skirmish/mapmanager.hpp"
#include "game/deploymentzone.hpp"

#include "gui/guihelper.hpp"

#include "gui/ng/radiotogglebutton.hpp"
#include "gui/ng/buttongroup.hpp"

#include "gui/cursor.hpp"

namespace qrw
{

DeployState::DeployState(sf::RenderWindow* renderWindow, MapManager& mapManager)
    : SceneState(renderWindow, EGameStateId::EGSID_DEPLOY_STATE),
	  toggleFlatModeHandler_(),
	  mapManager_(mapManager),
	  board_(nullptr),
      _toSkirmish(false)
{
	// Initialize tool bar
	sf::Vector2f buttonSize(200.0f, 50.0f);
	namelessgui::RadioToggleButton* radioButton = nullptr;
	std::shared_ptr<namelessgui::ButtonGroup> unitButtonGroup = std::make_shared<namelessgui::ButtonGroup>();

	// Player one tools
	playerOneNameLabel_ = new namelessgui::Text();
	playerOneNameLabel_->setText("Player One");
	playerOneNameLabel_->setAnchor({0.5f, 0.0f});
	playerOneNameLabel_->setParentAnchor({0.5f, 0.0f});
	_toolBar->addWidget(playerOneNameLabel_);

	radioButton = new namelessgui::RadioToggleButton(unitButtonGroup, "p1swordman");
	radioButton->setText(GuiHelper::getUnitName(EUT_SWORDMAN));
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, buttonSize.y});
	radioButton->setImage(GuiHelper::getUnitTexture(UNITTYPES::EUT_SWORDMAN, 1));
	radioButton->signalActivated.connect([this] { slotUnitButtonChanged(UNITTYPES::EUT_SWORDMAN, 0); });
	_toolBar->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(unitButtonGroup, "p1archer");
	radioButton->setText(GuiHelper::getUnitName(EUT_ARCHER));
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, 2 * buttonSize.y});
	radioButton->setImage(GuiHelper::getUnitTexture(UNITTYPES::EUT_ARCHER, 1));
	radioButton->signalActivated.connect([this] { slotUnitButtonChanged(UNITTYPES::EUT_ARCHER, 0); });
	_toolBar->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(unitButtonGroup, "p1spearman");
	radioButton->setText(GuiHelper::getUnitName(EUT_SPEARMAN));
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, 3 * buttonSize.y});
	radioButton->setImage(GuiHelper::getUnitTexture(UNITTYPES::EUT_SPEARMAN, 1));
	radioButton->signalActivated.connect([this] { slotUnitButtonChanged(UNITTYPES::EUT_SPEARMAN, 0); });
	_toolBar->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(unitButtonGroup, "p1laddercarrier");
	radioButton->setText(GuiHelper::getUnitName(EUT_LADDERCARRIER));
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({0.5f, 4 * buttonSize.y});
	radioButton->setImage(GuiHelper::getUnitTexture(UNITTYPES::EUT_LADDERCARRIER, 1));
	radioButton->signalActivated.connect([this] { slotUnitButtonChanged(UNITTYPES::EUT_LADDERCARRIER, 0); });
	_toolBar->addWidget(radioButton);

	// Player two tools
	playerTwoNameLabel_ = new namelessgui::Text();
	playerTwoNameLabel_->setText("Player Two");
	playerTwoNameLabel_->setAnchor({0.5f, 0.0f});
	playerTwoNameLabel_->setParentAnchor({0.5f, 0.4f});
	_toolBar->addWidget(playerTwoNameLabel_);

	radioButton = new namelessgui::RadioToggleButton(unitButtonGroup, "p2swordman");
	radioButton->setText(GuiHelper::getUnitName(EUT_SWORDMAN));
	radioButton->setSize(buttonSize);
	radioButton->setParentAnchor({0.0f, 0.4f});
	radioButton->setRelativePosition({5.0f, buttonSize.y});
	radioButton->setImage(GuiHelper::getUnitTexture(UNITTYPES::EUT_SWORDMAN, 2));
	radioButton->signalActivated.connect([this] { slotUnitButtonChanged(UNITTYPES::EUT_SWORDMAN, 1); });
	_toolBar->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(unitButtonGroup, "p2archer");
	radioButton->setText(GuiHelper::getUnitName(EUT_ARCHER));
	radioButton->setSize(buttonSize);
	radioButton->setParentAnchor({0.0f, 0.4f});
	radioButton->setRelativePosition({5.0f, 2 * buttonSize.y});
	radioButton->setImage(GuiHelper::getUnitTexture(UNITTYPES::EUT_ARCHER, 2));
	radioButton->signalActivated.connect([this] { slotUnitButtonChanged(UNITTYPES::EUT_ARCHER, 1); });
	_toolBar->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(unitButtonGroup, "p2spearman");
	radioButton->setText(GuiHelper::getUnitName(EUT_SPEARMAN));
	radioButton->setSize(buttonSize);
	radioButton->setParentAnchor({0.0f, 0.4f});
	radioButton->setRelativePosition({5.0f, 3 * buttonSize.y});
	radioButton->setImage(GuiHelper::getUnitTexture(UNITTYPES::EUT_SPEARMAN, 2));
	radioButton->signalActivated.connect([this] { slotUnitButtonChanged(UNITTYPES::EUT_SPEARMAN, 1); });
	_toolBar->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(unitButtonGroup, "p2laddercarrier");
	radioButton->setText(GuiHelper::getUnitName(EUT_LADDERCARRIER));
	radioButton->setSize(buttonSize);
	radioButton->setParentAnchor({0.0f, 0.4f});
	radioButton->setRelativePosition({0.5f, 4 * buttonSize.y});
	radioButton->setImage(GuiHelper::getUnitTexture(UNITTYPES::EUT_LADDERCARRIER, 2));
	radioButton->signalActivated.connect([this] { slotUnitButtonChanged(UNITTYPES::EUT_LADDERCARRIER, 1); });
	_toolBar->addWidget(radioButton);

	// Next step button
	namelessgui::Button* nextStepButton = new namelessgui::Button();
	nextStepButton->setText("Into Battle");
	nextStepButton->setSize({buttonSize.x, 30.0f});
	nextStepButton->setAnchor({0.5f, 1.0f});
	nextStepButton->setParentAnchor({0.5f, 1.0f});
	nextStepButton->setRelativePosition({0.0f, -5.0f});
    nextStepButton->signalClicked.connect([this] { slotToSkirmishButtonClicked(); });
	_toolBar->addWidget(nextStepButton);

	// Error dialog
	errorDialog_ = new namelessgui::MessageDialog();
	errorDialog_->signalClosed.connect([this] { _backToMainMenu = true; });
	errorDialog_->setAnchor({0.5, 0.5});
	errorDialog_->setParentAnchor({0.5, 0.5});
	errorDialog_->setVisible(false);
	_guiUptr->addWidget(errorDialog_);
}

DeployState::~DeployState()
{
	for(auto& zoneIter : deploymentZones_)
		g_scene.destroy(zoneIter.second);
}

EGameStateId DeployState::update()
{
	if(_backToMainMenu)
		return EGameStateId::EGSID_MAIN_MENU_STATE;

	if(_toSkirmish)
		return EGameStateId::EGSID_SKIRMISH_STATE;

	return EGameStateId::EGSID_NO_CHANGE;
}

void DeployState::init(GameState* previousState)
{
	assert(previousState->getId() == EGameStateId::EGSID_SKIRMISH_PREPARATION_STATE);
	const SkirmishPreparationState* preparationState = static_cast<const SkirmishPreparationState*>(previousState);

	SceneState::init(previousState);

	// Load board
	MapManager::LoadErrors error;
	MapDto dto = mapManager_.loadMap(preparationState->getMapName(), error);

	// TODO show error
	if(error != MapManager::LoadErrors::SUCCESS)
	{
		handleMapLoadingError();
		return;
	}

	if(dto.deploymentZones.size() < 2)
	{
		handleMapLoadingError();
		return;
	}

	board_ = dto.board;
	g_scene.setBoard(board_);
	for(auto& deploymentZone : dto.deploymentZones)
	{
		g_scene.addGameObject(deploymentZone);
		deploymentZones_[deploymentZone->getPlayerId()] = deploymentZone;
	}

	for(const auto& terrainIter : board_->getTerrains())
	{
		g_scene.addGameObject(terrainIter.second);
	}

	for(const auto& structureIter : board_->getStructures())
	{
		g_scene.addGameObject(structureIter.second);
	}

	g_scene.spawn<Cursor>();

	SkirmishCamera* camera = g_scene.spawn<SkirmishCamera>();
	camera->setCenter(board_->getFirstComponent<BoardBackgroundComponent>()->getViewCenter());

	// Create new players
	_players.clear();
	_players.push_back(std::make_shared<Player>());
	_players[0]->setId(1);
	_players[0]->setName(preparationState->getPlayerOneName());
	_players.push_back(std::make_shared<Player>());
	_players[1]->setId(2);
	_players[1]->setName(preparationState->getPlayerTwoName());

	playerOneNameLabel_->setText(preparationState->getPlayerOneName());
	playerTwoNameLabel_->setText(preparationState->getPlayerTwoName());

    _toSkirmish = false;
}

Board* DeployState::getBoard() const
{
	return board_;
}

std::vector<Player::Ptr> DeployState::getPlayers() const
{
    return _players;
}

void DeployState::slotUnitButtonChanged(UNITTYPES unitType, unsigned int playerNumber)
{
	_selectedPlayer = _players.at(playerNumber);
	_selectedUnitType = unitType;
}

void DeployState::slotToSkirmishButtonClicked()
{
    _toSkirmish = true;
}

void DeployState::slotCursorLeftClicked(const Coordinates& boardPosition)
{
	if(_selectedPlayer == nullptr)
		return;

	if(!deploymentZones_.at(_selectedPlayer->getId())->containsSquare(boardPosition))
		return;

	if(Unit* unit = board_->getUnit(boardPosition))
		g_scene.destroy(unit);

	Unit* unit = UnitFactory::createUnit(_selectedUnitType, _selectedPlayer);
	unit->deploy(boardPosition);
	unit->setFlatMode(toggleFlatModeHandler_.isFlatMode());
	g_scene.addGameObject(unit);
}

void DeployState::slotCursorRightClicked(const Coordinates &boardPosition)
{
	if(Unit* unit = board_->getUnit(boardPosition))
		g_scene.destroy(unit);
}

void DeployState::handleMapLoadingError()
{
	errorDialog_->setVisible();
	errorDialog_->setMessage("The selected map could not be loaded. Please report this to the author of the map.");
	errorDialog_->setButtonText("Back to main menu");
	_toolBar->setVisible(false);
}

} // namespace qrw
