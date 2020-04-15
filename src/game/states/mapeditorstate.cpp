#include "game/states/mapeditorstate.hpp"

#include "engine/terrain.hpp"

#include "gui/texturemanager.hpp"

#include "game/cameras/skirmishcamera.hpp"
#include "game/deploymentzone.hpp"
#include "game/skirmish/structure.hpp"
#include "game/skirmish/stairs.hpp"
#include "game/skirmish/boardbackgroundcomponent.hpp"
#include "game/skirmish/flatmodeawaremixin.hpp"

namespace qrw
{

MapEditorState::MapEditorState(sf::RenderWindow* renderWindow, MapManager& mapManager, SkirmishGuiFactory& guiFactory)
	: SceneState(renderWindow, EGameStateId::EGSID_MAP_EDITOR_STATE),
	  toggleFlatModeHandler_(),
	  mapManager(mapManager)
{
	cursorMode_ = CursorMode::PLACE_TERRAIN;
	selectedEntity_.terrainType = TERRAINTYPES::ET_WOOD;

	// Gui
	auto mapEditorToolBar = guiFactory.createMapEditorToolBar(INITIAL_BOARD_WIDTH, INITIAL_BOARD_HEIGHT);
	mapEditorToolBar->setSize(_toolBar->getSize());
	mapEditorToolBar->signalLoadClicked.connect([this] (const std::string mapName) { slotLoadClicked(mapName); });
	mapEditorToolBar->signalSaveClicked.connect([this] (const std::string mapName) { slotSaveClicked(mapName); });
	mapEditorToolBar->signalBoardWidthChanged.connect([this] (unsigned int width) { slotChangeBoardWidth(width); });
	mapEditorToolBar->signalBoardHeightChanged.connect([this] (unsigned int height) { slotChangeBoardHeight(height); });
	mapEditorToolBar->signalTerrainTypeClicked.connect([this] (TERRAINTYPES terrainType) { setCursorModePlaceTerrain(terrainType); });
	mapEditorToolBar->signalEraseTerrainClicked.connect([this] () { setCursorModeEraseterrain(); });
	mapEditorToolBar->signalStructureClicked.connect([this] (Structure::Type type) { setCursorModePlaceStructure(type); });
	mapEditorToolBar->signalEraseStructureClicked.connect([this] () { setCursorModeEraseStructure(); });
	mapEditorToolBar->signalDeploymentZoneClicked.connect([this] (unsigned int playerNumber) { setCursorModePlaceDeploymentZone(playerNumber); });
	mapEditorToolBar->signalEraseDeploymentZoneClicked.connect([this] () { setCursorModeEraseDeploymentZone(); });
	_toolBar->addWidget(mapEditorToolBar);

	mapOverwriteConfirmationDialog_ = new namelessgui::ConfirmationDialog("Map already exists!\nOverwrite existing map?");
	mapOverwriteConfirmationDialog_->setSize({250, 100});
	mapOverwriteConfirmationDialog_->signalYesClicked.connect([this] () { saveMap(mapNameForSaveConfirmation_); });
	_guiUptr->addWidget(mapOverwriteConfirmationDialog_);
	mapOverwriteConfirmationDialog_->setVisible(false);
}

void MapEditorState::init(GameState* previousState)
{
	g_scene.reset();
	SceneState::init(previousState);

	_spBoard = g_scene.spawn<qrw::Board>();
	_spBoard->setWidth(INITIAL_BOARD_WIDTH);
	_spBoard->setHeight(INITIAL_BOARD_HEIGHT);

	g_scene.spawn<Cursor>();

	deploymentZones_.push_back(g_scene.spawn<DeploymentZone>());
	deploymentZones_.at(0)->setPlayerId(1);
	deploymentZones_.push_back(g_scene.spawn<DeploymentZone>());
	deploymentZones_.at(1)->setPlayerId(2);

	SkirmishCamera* camera = g_scene.spawn<SkirmishCamera>();
	camera->setCenter(_spBoard->getFirstComponent<BoardBackgroundComponent>()->getViewCenter());
}

EGameStateId MapEditorState::update()
{
	if(_backToMainMenu)
		return EGameStateId::EGSID_MAIN_MENU_STATE;

	return EGameStateId::EGSID_NO_CHANGE;
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
		placeDeploymentZone(boardPosition, selectedEntity_.playerNumber);
		break;
	case CursorMode::ERASE_DEPLOYMENTZONE:
		eraseDeploymentZone(boardPosition);
		break;
	case CursorMode::PLACE_STRUCTURE:
		placeStructure(boardPosition, selectedEntity_.structure);
		break;
	case CursorMode::ERASE_STRUCTURE:
		eraseStructure(boardPosition);
		break;
	} // switch
}

void MapEditorState::slotCursorRightClicked(const Coordinates& boardPosition)
{
	if(Terrain* terrain = _spBoard->getTerrain(boardPosition))
		g_scene.destroy(terrain);

	if(Stairs* stairs = dynamic_cast<Stairs*>(_spBoard->getStructure(boardPosition)))
		stairs->rotate();
}

void MapEditorState::slotChangeBoardWidth(unsigned int width)
{
	_spBoard->setWidth(width);
	despawnTerrainNotOnBoard();
	despawnStructuresNotOnBoard();
	cropDeploymentZones();
}

void MapEditorState::slotChangeBoardHeight(unsigned int height)
{
	_spBoard->setHeight(height);
	despawnTerrainNotOnBoard();
	despawnStructuresNotOnBoard();
	cropDeploymentZones();
}

void MapEditorState::despawnTerrainNotOnBoard()
{
	for(auto& terrainIter : _spBoard->getTerrains())
	{
		if(!_spBoard->isOnBoard(terrainIter.first))
		{
			_spBoard->removeTerrain(terrainIter.first);
			g_scene.destroy(terrainIter.second);
		}
	}
}

void MapEditorState::despawnStructuresNotOnBoard()
{
	for(auto& structureIter : _spBoard->getStructures())
	{
		if(!_spBoard->isOnBoard(structureIter.first))
		{
			_spBoard->removeStructureAt(structureIter.first);
			g_scene.destroy(structureIter.second);
		}
	}
}

void MapEditorState::cropDeploymentZones()
{
	for(auto& deploymentZone : deploymentZones_)
	{
		deploymentZone->crop({(int)_spBoard->getWidth(), (int)_spBoard->getHeight()});
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

void MapEditorState::setCursorModePlaceStructure(Structure::Type type)
{
	cursorMode_ = CursorMode::PLACE_STRUCTURE;
	selectedEntity_.structure = type;
}

void MapEditorState::setCursorModeEraseStructure()
{
	cursorMode_ = CursorMode::ERASE_STRUCTURE;
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

void MapEditorState::slotSaveClicked(const std::string& mapName)
{
	if(!mapManager.doesMapExist(mapName))
		saveMap(mapName);
	else
	{
		mapNameForSaveConfirmation_ = mapName;
		mapOverwriteConfirmationDialog_->setVisible(true);
	}
}

void MapEditorState::slotLoadClicked(const std::string& mapName)
{
	if(!mapManager.doesMapExist(mapName))
		return;

	// Clean up
	for(auto& terrainIter : _spBoard->getTerrains()) g_scene.destroy(terrainIter.second);
	for(auto& deploymentZone : deploymentZones_) g_scene.destroy(deploymentZone);
	for(auto& structureIter : _spBoard->getStructures()) g_scene.destroy(structureIter.second);

	g_scene.destroy(_spBoard);
	_spBoard = nullptr;
	deploymentZones_.clear();

	// Load and add objects
	MapManager::LoadErrors error;
	MapDto dto = mapManager.loadMap(mapName, error);

	// TODO error handling

	_spBoard = dto.board;
	deploymentZones_ = dto.deploymentZones;

	g_scene.addGameObject(_spBoard);
	for(auto& deploymentZone : deploymentZones_) g_scene.addGameObject(deploymentZone);
	for(auto& terrainIter : _spBoard->getTerrains()) g_scene.addGameObject(terrainIter.second);
	for(auto& structureIter : _spBoard->getStructures()) g_scene.addGameObject(structureIter.second);
}

void MapEditorState::placeTerrain(const Coordinates& boardPosition, TERRAINTYPES terrainType)
{
	Terrain* terrain = Terrain::createTerrain(terrainType);
	if(terrain != nullptr)
	{
		eraseTerrain(boardPosition);
		eraseStructure(boardPosition);

		_spBoard->setTerrain(boardPosition, terrain);
		terrain->setPosition(boardPosition);
		g_scene.addGameObject(terrain);
	}
}

void MapEditorState::eraseTerrain(const Coordinates& boardPosition)
{
	if(_spBoard->isTerrainAt(boardPosition))
	{
		g_scene.destroy(_spBoard->getTerrain(boardPosition));
		_spBoard->removeTerrain(boardPosition);
	}
}

void MapEditorState::placeStructure(const Coordinates& position, Structure::Type structureId)
{
	eraseTerrain(position);
	eraseStructure(position);

	auto structure = structureFactory_.createStructure(structureId);
	structure->setPosition(position);

	if(auto flatModeAwareStructure = dynamic_cast<FlatModeAwareMixin*>(structure)) {
		flatModeAwareStructure->setFlatMode(toggleFlatModeHandler_.isFlatMode());
	}

	g_scene.addGameObject(structure);
	_spBoard->setStructure(position, structure);
}

void MapEditorState::eraseStructure(const Coordinates& position)
{
	if(auto structure = _spBoard->getStructure(position))
	{
		_spBoard->removeStructureAt(position);
		g_scene.destroy(structure);
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
		if(deploymentZone->containsSquare(boardPosition))
			deploymentZone->removeSquare(boardPosition);
	}
}

void MapEditorState::saveMap(const std::string& mapName)
{
	MapDto dto;
	dto.board = _spBoard;
	dto.deploymentZones = deploymentZones_;
	mapManager.saveMap(mapName, dto);
}

} // namespace qrw
