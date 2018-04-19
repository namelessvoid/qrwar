#include "game/states/mapeditorstate.hpp"

#include "engine/terrain.hpp"

#include "gui/texturemanager.hpp"

#include "gui/ng/buttongroup.hpp"
#include "gui/ng/tabwidget.hpp"
#include "gui/ng/spinbox.hpp"
#include "gui/ng/lineinput.hpp"

#include "game/cameras/skirmishcamera.hpp"
#include "game/deploymentzone.hpp"
#include "game/mapmanager.hpp"
#include "game/constants.hpp"

#include "foundation/spritecomponent.hpp"

namespace qrw
{

MapEditorState::MapEditorState(sf::RenderWindow* renderWindow)
	: SceneState(renderWindow, EGameStateId::EGSID_MAP_EDITOR_STATE)
{
	cursorMode_ = CursorMode::PLACE_TERRAIN;
	selectedEntity_.terrainType = TERRAINTYPES::ET_WOOD;

	// Gui
	TextureManager* textureManager = TextureManager::getInstance();

	namelessgui::TabWidget* tabWidget = new namelessgui::TabWidget();
	tabWidget->setSize(_toolBar->getSize());
	tabWidget->setButtonSize({48, 48});
	tabWidget->addTab(textureManager->getTexture("wheel"), createConfigToolsWindow());
	tabWidget->addTab(textureManager->getTexture("wood"), createTerrainToolsWindow());
	tabWidget->addTab(textureManager->getTexture("wall"), createStructureToolsWindow());
	tabWidget->addTab(textureManager->getTexture("default"), createDeploymentZoneToolsWindow());
	_toolBar->addWidget(tabWidget);

	mapOverwriteConfirmationDialog_ = new namelessgui::ConfirmationDialog("Map already exists!\nOverwrite existing map?");
	mapOverwriteConfirmationDialog_->setSize({250, 100});
	mapOverwriteConfirmationDialog_->signalYesClicked.connect([this] { saveMap(); });
	_guiUptr->addWidget(mapOverwriteConfirmationDialog_);
	mapOverwriteConfirmationDialog_->setVisible(false);
}

MapEditorState::~MapEditorState()
{
}

void MapEditorState::init(GameState* previousState)
{
	g_scene.reset();
	SceneState::init(previousState);

	_spBoard = new Board(INITIAL_BOARD_WIDTH, INITIAL_BOARD_HEIGHT);
	g_scene.setBoard(_spBoard);

	g_scene.spawn<Cursor>();

	deploymentZones_.push_back(g_scene.spawn<DeploymentZone>());
	deploymentZones_.at(0)->setPlayerId(1);
	deploymentZones_.push_back(g_scene.spawn<DeploymentZone>());
	deploymentZones_.at(1)->setPlayerId(2);

	SkirmishCamera* camera = g_scene.spawn<SkirmishCamera>();
	camera->setCenter(_spBoard->getComponent<SpriteComponent>()->getCenter());
}

EGameStateId MapEditorState::update()
{
	if(_backToMainMenu)
		return EGameStateId::EGSID_MAIN_MENU_STATE;

	return EGameStateId::EGSID_NO_CHANGE;
}

Board* MapEditorState::getBoard() const
{
	return _spBoard;
}

void MapEditorState::slotCursorLeftClicked(const Coordinates& boardPosition)
{
	switch(cursorMode_)
	{
	case CursorMode::PLACE_TERRAIN:
		placeTerrain(boardPosition, selectedEntity_.terrainType);
		break;
	case CursorMode::ERASE_TERRAIN:
		eraseTerrain(boardPosition);
		break;
	case CursorMode::PLACE_DEPLOYMENTZONE:
	{
		placeDeploymentZone(boardPosition, selectedEntity_.playerNumber);
		break;
	}
	case CursorMode::ERASE_DEPLOYMENTZONE:
		eraseDeploymentZone(boardPosition);
		break;
	case CursorMode::PLACE_STRUCTURE:
	case CursorMode::ERASE_STRUCTURE:
	{
		break;
	}
	} // switch
}

void MapEditorState::slotCursorRightClicked(const Coordinates& boardPosition)
{
	if(Terrain* terrain = _spBoard->getTerrain(boardPosition))
		g_scene.despawn(terrain);
}

void MapEditorState::slotChangeBoardWidth(unsigned int width)
{
	_spBoard->setWidth(width);
	despawnTerrainNotOnBoard();
}

void MapEditorState::slotChangeBoardHeight(unsigned int height)
{
	_spBoard->setHeight(height);
	despawnTerrainNotOnBoard();
}

void MapEditorState::despawnTerrainNotOnBoard()
{
	for(auto& terrainIter : _spBoard->getTerrains())
	{
		if(!_spBoard->isOnBoard(terrainIter.first))
		{
			_spBoard->removeTerrain(terrainIter.first);
			g_scene.despawn(terrainIter.second);
		}
	}
}

void MapEditorState::setCursorModePlaceTerrain(TERRAINTYPES terrainType)
{
	cursorMode_ = CursorMode::PLACE_TERRAIN;
	selectedEntity_.terrainType = terrainType;
}

void MapEditorState::setCursorModeEraseterrain()
{
	cursorMode_ = CursorMode::ERASE_TERRAIN;
}

void MapEditorState::setCursorModePlaceDeploymentZone(unsigned int playerNumber)
{
	cursorMode_ = CursorMode::PLACE_DEPLOYMENTZONE;
	selectedEntity_.playerNumber = playerNumber;
}

void MapEditorState::setCursorModeEraseDeploymentZone()
{
	cursorMode_ = CursorMode::ERASE_DEPLOYMENTZONE;	
}

void MapEditorState::slotSaveButtonClicked()
{
	MapManager* mapManager = MapManager::get();

	if(!mapManager->doesMapExist(mapNameInput_->getText()))
		saveMap();
	else
		mapOverwriteConfirmationDialog_->setVisible(true);
}

void MapEditorState::slotLoadButtonClicked()
{
	MapManager* mapManager = MapManager::get();

	if(!mapManager->doesMapExist(mapNameInput_->getText()))
		return;

	// Clean up
	for(auto& terrainIter : _spBoard->getTerrains()) g_scene.despawn(terrainIter.second);
	g_scene.despawn(_spBoard);
	_spBoard = nullptr;
	for(auto& deploymentZone : deploymentZones_) g_scene.despawn(deploymentZone);
	deploymentZones_.clear();

	// Load and add objects
	MapManager::LoadErrors error = mapManager->loadMap(
		mapNameInput_->getText(),
		_spBoard,
		deploymentZones_);

	// TODO error handling

	g_scene.addGameObject(_spBoard);
	for(auto& deploymentZone : deploymentZones_) g_scene.addGameObject(deploymentZone);
}

void MapEditorState::placeTerrain(const Coordinates& boardPosition, TERRAINTYPES terrainType)
{
	Terrain* terrain = Terrain::createTerrain(terrainType);
	if(terrain != nullptr)
	{
		if(Terrain* oldTerrain = _spBoard->getTerrain(boardPosition))
			g_scene.despawn(oldTerrain);

		_spBoard->setTerrain(boardPosition, terrain);
		terrain->setPosition(boardPosition);
		g_scene.addGameObject(terrain);
	}
}

void MapEditorState::eraseTerrain(const Coordinates& boardPosition)
{
	if(_spBoard->isTerrainAt(boardPosition))
	{
		g_scene.despawn(_spBoard->getTerrain(boardPosition));
	}
}

void MapEditorState::placeDeploymentZone(const Coordinates& boardPosition, unsigned int playerNumber)
{
	eraseDeploymentZone(boardPosition);
	deploymentZones_.at(selectedEntity_.playerNumber)->addSquare(boardPosition);
}

void MapEditorState::eraseDeploymentZone(const Coordinates& boardPosition)
{
	for(auto& deploymentZone : deploymentZones_)
	{
		deploymentZone->removeSquare(boardPosition);
	}
}

void MapEditorState::saveMap()
{
	MapManager::get()->saveMap(
		mapNameInput_->getText(),
		*_spBoard,
		deploymentZones_);
}

namelessgui::Window* MapEditorState::createConfigToolsWindow()
{
	namelessgui::Window* configWindow = new namelessgui::Window();

	sf::Vector2f buttonSize(140.0f, 50.0f);

	namelessgui::Text* heading = new namelessgui::Text();
	heading->setText("Settings");
	heading->setRelativePosition({5.0f, 0});
	configWindow->addWidget(heading);

	mapNameInput_ = new namelessgui::LineInput();
	mapNameInput_->setSize({198, 30});
	mapNameInput_->setText("Map Name");
	configWindow->addWidget(mapNameInput_);

	namelessgui::SpinBox* mapWidthBox = new namelessgui::SpinBox();
	mapWidthBox->setSize({100.0f, 30.0f});
	mapWidthBox->setRelativePosition({0, 50});
	mapWidthBox->setMinValue(10);
	mapWidthBox->setMaxValue(128);
	mapWidthBox->setValue(INITIAL_BOARD_WIDTH);
	mapWidthBox->signalChanged.connect([this] (unsigned int width) { slotChangeBoardWidth(width); });
	configWindow->addWidget(mapWidthBox);

	namelessgui::SpinBox* mapHeightBox = new namelessgui::SpinBox();
	mapHeightBox->setSize({100.0f, 30.0f});
	mapHeightBox->setRelativePosition({0, 50});
	mapHeightBox->setMinValue(10);
	mapHeightBox->setMaxValue(128);
	mapHeightBox->setValue(INITIAL_BOARD_HEIGHT);
	mapHeightBox->setAnchor({1, 0});
	mapHeightBox->setParentAnchor({1, 0});
	mapHeightBox->signalChanged.connect([this] (unsigned int height) { slotChangeBoardHeight(height); });
	configWindow->addWidget(mapHeightBox);

	namelessgui::Button* saveButton = new namelessgui::Button();
	saveButton->setText("Save");
	saveButton->setSize({buttonSize.x, 30.0f});
	saveButton->setAnchor({0.5f, 1.0f});
	saveButton->setParentAnchor({0.5f, 1.0f});
	saveButton->setRelativePosition({0.0f, -5.0f});
	saveButton->signalClicked.connect(std::bind(&MapEditorState::slotSaveButtonClicked, this));
	configWindow->addWidget(saveButton);

	namelessgui::Button* loadButton = new namelessgui::Button();
	loadButton->setText("Load");
	loadButton->setRelativePosition({0, 150});
	loadButton->setSize({150, 30});
	loadButton->signalClicked.connect([this] { slotLoadButtonClicked(); });
	configWindow->addWidget(loadButton);

	return configWindow;
}

namelessgui::Window* MapEditorState::createTerrainToolsWindow()
{
	namelessgui::Window* terrainWindow = new namelessgui::Window();

	sf::Vector2f buttonSize(140.0f, 50.0f);
	float buttonYOffset = 45;

	namelessgui::Text* heading = new namelessgui::Text();
	heading->setText("Terrain");
	heading->setRelativePosition({5.0f, 0});
	terrainWindow->addWidget(heading);

	std::shared_ptr<namelessgui::ButtonGroup> spTerrainButtonGroup = std::make_shared<namelessgui::ButtonGroup>();
	namelessgui::RadioToggleButton* radioButton = new namelessgui::RadioToggleButton(spTerrainButtonGroup, "Wood");
	radioButton->setText("Wood");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, buttonYOffset});
	radioButton->setImage(TextureManager::getInstance()->getTexture("wood"));
	radioButton->signalActivated.connect([this] { setCursorModePlaceTerrain(TERRAINTYPES::ET_WOOD); });
	terrainWindow->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(spTerrainButtonGroup, "Hill");
	radioButton->setText("Hill");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, 1 * buttonSize.y + buttonYOffset});
	radioButton->setImage(TextureManager::getInstance()->getTexture("hill"));
	radioButton->signalActivated.connect([this] { setCursorModePlaceTerrain(TERRAINTYPES::ET_HILL); });
	terrainWindow->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(spTerrainButtonGroup, "Wall");
	radioButton->setText("Wall");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, 2 * buttonSize.y + buttonYOffset});
	radioButton->setImage(TextureManager::getInstance()->getTexture("wall"));
	radioButton->signalActivated.connect([this] { setCursorModePlaceTerrain(TERRAINTYPES::ET_WALL); });
	terrainWindow->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(spTerrainButtonGroup, "Erase");
	radioButton->setText("Erase");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, 3 * buttonSize.y + buttonYOffset});
	radioButton->setImage(TextureManager::getInstance()->getTexture("default"));
	radioButton->signalActivated.connect([this] { setCursorModeEraseterrain(); });
	terrainWindow->addWidget(radioButton);

	return terrainWindow;
}

namelessgui::Window* MapEditorState::createStructureToolsWindow()
{
	namelessgui::Window* structureWindow = new namelessgui::Window();

	namelessgui::Text* heading = new namelessgui::Text();
	heading->setText("Structures");
	heading->setRelativePosition({5.0f, 0});
	structureWindow->addWidget(heading);

	return structureWindow;
}

namelessgui::Window* MapEditorState::createDeploymentZoneToolsWindow()
{
	sf::Vector2f buttonSize(140.0f, 50.0f);
	float buttonYOffset = 45;

	namelessgui::Window* zoneWindow = new namelessgui::Window();

	namelessgui::Text* heading = new namelessgui::Text();
	heading->setText("Deployment Zones");
	heading->setRelativePosition({5.0f, 0});
	zoneWindow->addWidget(heading);

	std::shared_ptr<namelessgui::ButtonGroup> zoneButtonGroup = std::make_shared<namelessgui::ButtonGroup>();
	namelessgui::RadioToggleButton* radioButton = new namelessgui::RadioToggleButton(zoneButtonGroup, "Player1");
	radioButton->setText("Player 1");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, buttonYOffset});
	radioButton->setImage(TextureManager::getInstance()->getTexture("default"));
	radioButton->signalActivated.connect([this] { setCursorModePlaceDeploymentZone(0); });
	zoneWindow->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(zoneButtonGroup, "Player2");
	radioButton->setText("Player 2");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, 1 * buttonSize.y + buttonYOffset});
	radioButton->setImage(TextureManager::getInstance()->getTexture("default"));
	radioButton->signalActivated.connect([this] { setCursorModePlaceDeploymentZone(1); });
	zoneWindow->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(zoneButtonGroup, "Erase");
	radioButton->setText("Erase");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, 2 * buttonSize.y + buttonYOffset});
	radioButton->setImage(TextureManager::getInstance()->getTexture("default"));
	radioButton->signalActivated.connect([this] { setCursorModeEraseDeploymentZone(); });
	zoneWindow->addWidget(radioButton);

	return zoneWindow;
}

} // namespace qrw
