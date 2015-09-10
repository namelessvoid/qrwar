#include "gamestates/mapeditorstate.hpp"

#include "engine/terrain.hpp"
#include "engine/square.hpp"

#include "gui/texturemanager.hpp"
#include "config/settings.hpp"

#include <iostream>

namespace qrw
{

MapEditorState::MapEditorState(sf::RenderWindow* renderWindow)
	: SceneState(renderWindow, EGameStateId::EGSID_MAP_EDITOR_STATE),
	  _activeTerrainType(ET_NUMBEROFTERRAINTYPES)
{
	// Initialize toolbar
	_toolBar = new namelessgui::Window();
	_toolBar->setVisible(true);
	_toolBar->setSize({150.0f, (float)Settings::getInstance()->getResolutionY()});
	_toolBar->setAnchor({1.0f, 0.0f});
	_toolBar->setParentAnchor({1.0f, 0.0f});
	_toolBar->setVisible(true);
	_guiUptr->addWidget(_toolBar);

	namelessgui::Label* label = new namelessgui::Label();
	label->setText("Terrain");
	label->setAnchor({0.5f, 0.0f});
	label->setParentAnchor({0.5f, 0.0f});
	_toolBar->addWidget(label);

	sf::Vector2f buttonSize(140.0f, 50.0f);

	namelessgui::RadioToggleButton* radioButton = new namelessgui::RadioToggleButton();
	std::shared_ptr<namelessgui::ButtonGroup> spTerrainButtonGroup = radioButton->getButtonGroup();
	radioButton->setText("Wood");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, buttonSize.y});
	radioButton->setImage(TextureManager::getInstance()->getTexture("wood"));
	radioButton->signalActivated.connect(std::bind(&MapEditorState::slotTerrainButtonChanged, this, std::placeholders::_1));
	_toolBar->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(spTerrainButtonGroup);
	radioButton->setText("Hill");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, 2 * buttonSize.y});
	radioButton->setImage(TextureManager::getInstance()->getTexture("hill"));
	radioButton->signalActivated.connect(std::bind(&MapEditorState::slotTerrainButtonChanged, this, std::placeholders::_1));
	_toolBar->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(spTerrainButtonGroup);
	radioButton->setText("Wall");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, 3 * buttonSize.y});
	radioButton->setImage(TextureManager::getInstance()->getTexture("wall"));
	radioButton->signalActivated.connect(std::bind(&MapEditorState::slotTerrainButtonChanged, this, std::placeholders::_1));
	_toolBar->addWidget(radioButton);

	namelessgui::Button* toDeploymentButton = new namelessgui::Button();
	toDeploymentButton->setText("next step");
	toDeploymentButton->setSize({buttonSize.x, 30.0f});
	toDeploymentButton->setAnchor({0.5f, 1.0f});
	toDeploymentButton->setParentAnchor({0.5f, 1.0f});
	toDeploymentButton->setRelativePosition({0.0f, -50.0f});
	toDeploymentButton->signalclicked.connect(std::bind(&MapEditorState::slotToDeploymentButtonClicked, this));
	_toolBar->addWidget(toDeploymentButton);
}

MapEditorState::~MapEditorState()
{
}

void MapEditorState::init(GameState* previousState)
{
	GameState::init();

	_toDeployment = false;
	_backToMainMenu = false;
	_spBoard = std::make_shared<Board>(16, 9);
	_scene = std::unique_ptr<Scene>(new Scene(_renderWindow, _spBoard));

	_scene->signalCursorLeftClicked.connect(std::bind(&MapEditorState::slotCursorLeftClicked, this, std::placeholders::_1));
	_scene->signalCursorRightClicked.connect(std::bind(&MapEditorState::slotCursorRightClicked, this, std::placeholders::_1));
}

EGameStateId MapEditorState::update()
{
	if(_backToMainMenu)
		return EGameStateId::EGSID_MAIN_MENU_STATE;

	if(_toDeployment)
		return EGameStateId::EGSID_DEPLOY_STATE;

	return EGameStateId::EGSID_NO_CHANGE;
}

bool MapEditorState::handleEvent(sf::Event& event)
{
	bool stopEventPropagation = SceneState::handleEvent(event);

	return stopEventPropagation;
}

void MapEditorState::slotCursorLeftClicked(const Coordinates& boardPosition)
{
	// Do nothing if no terrain type was selected
	if(_activeTerrainType == ET_NUMBEROFTERRAINTYPES)
		return;

	// Create new terrain
	Terrain::Ptr terrain = Terrain::createTerrain(_activeTerrainType);
	if(terrain != nullptr)
	{
		_spBoard->getSquare(boardPosition)->setTerrain(terrain);
		_scene->addTerrainEntity(TerrainEntity::createTerrainEntity(terrain, 32));
	}
}

void MapEditorState::slotCursorRightClicked(const Coordinates& boardPosition)
{
	_spBoard->getSquare(boardPosition)->setTerrain(nullptr);
	_scene->removeTerrainEntityAt(boardPosition);
}

void MapEditorState::slotTerrainButtonChanged(const namelessgui::RadioToggleButton& activeTerrainButton)
{
	const std::string& terrainString = activeTerrainButton.getText();

	if(terrainString == "Wood")
		_activeTerrainType = ET_WOOD;
	else if(terrainString == "Hill")
		_activeTerrainType = ET_HILL;
	else if(terrainString == "Wall")
		_activeTerrainType = ET_WALL;
	else
		_activeTerrainType = ET_NUMBEROFTERRAINTYPES;
}

void MapEditorState::slotToDeploymentButtonClicked()
{
	_toDeployment = true;
}

} // namespace qrw
