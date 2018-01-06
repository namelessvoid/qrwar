#include "game/states/mapeditorstate.hpp"

#include "engine/terrain.hpp"

#include "gui/texturemanager.hpp"

#include "gui/ng/buttongroup.hpp"
#include "gui/ng/tabwidget.hpp"

namespace qrw
{

MapEditorState::MapEditorState(sf::RenderWindow* renderWindow)
	: SceneState(renderWindow, EGameStateId::EGSID_MAP_EDITOR_STATE),
      _activeTerrainType(ET_NUMBEROFTERRAINTYPES),
      _eraseMode(false)
{
	namelessgui::TabWidget* tabWidget = new namelessgui::TabWidget();
	tabWidget->setSize(_toolBar->getSize());
	tabWidget->setButtonSize({64, 64});
	tabWidget->addTab(TextureManager::getInstance()->getTexture("wheel"), createConfigToolsWindow());
	tabWidget->addTab(TextureManager::getInstance()->getTexture("wheel"), createTerrainToolsWindow());
	_toolBar->addWidget(tabWidget);
}

MapEditorState::~MapEditorState()
{
}

void MapEditorState::init(GameState* previousState)
{
	g_scene.reset();
	SceneState::init(previousState);

	_spBoard = new Board(16, 9);
	g_scene.setBoard(_spBoard);

	g_scene.spawn<Cursor>();
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
    // Erase terrain
	if(_eraseMode && _spBoard->isTerrainAt(boardPosition))
    {
		g_scene.despawn(_spBoard->getTerrain(boardPosition));
    }
    // Place terrain
    else
    {
        // Do nothing if no terrain type was selected and erase mode is off.
        if(_activeTerrainType == ET_NUMBEROFTERRAINTYPES)
            return;

        Terrain* terrain = Terrain::createTerrain(_activeTerrainType);
        if(terrain != nullptr)
        {
			if(Terrain* oldTerrain = _spBoard->getTerrain(boardPosition))
				g_scene.despawn(oldTerrain);

			_spBoard->setTerrain(boardPosition, terrain);
			terrain->setPosition(boardPosition);
			g_scene.addGameObject(terrain);
        }
    }
}

void MapEditorState::slotCursorRightClicked(const Coordinates& boardPosition)
{
	if(Terrain* terrain = _spBoard->getTerrain(boardPosition))
		g_scene.despawn(terrain);
}

void MapEditorState::slotTerrainButtonChanged(const namelessgui::RadioToggleButton& activeTerrainButton)
{
	const std::string& buttonId = activeTerrainButton.getId();

	if(buttonId == "Wood")
		_activeTerrainType = ET_WOOD;
	else if(buttonId == "Hill")
		_activeTerrainType = ET_HILL;
	else if(buttonId == "Wall")
		_activeTerrainType = ET_WALL;
    else
		_activeTerrainType = ET_NUMBEROFTERRAINTYPES;

    if(buttonId == "Erase")
        _eraseMode = true;
    else
        _eraseMode = false;
}

void MapEditorState::slotSaveButtonClicked()
{
}

namelessgui::Window* MapEditorState::createConfigToolsWindow()
{
	namelessgui::Window* configWindow = new namelessgui::Window();

	sf::Vector2f buttonSize(140.0f, 50.0f);

	namelessgui::Button* toDeploymentButton = new namelessgui::Button();
	toDeploymentButton->setText("Save");
	toDeploymentButton->setSize({buttonSize.x, 30.0f});
	toDeploymentButton->setAnchor({0.5f, 1.0f});
	toDeploymentButton->setParentAnchor({0.5f, 1.0f});
	toDeploymentButton->setRelativePosition({0.0f, -5.0f});
	toDeploymentButton->signalclicked.connect(std::bind(&MapEditorState::slotSaveButtonClicked, this));
	configWindow->addWidget(toDeploymentButton);

	return configWindow;
}

namelessgui::Window* MapEditorState::createTerrainToolsWindow()
{
	namelessgui::Window* terrainWindow = new namelessgui::Window();

	sf::Vector2f buttonSize(140.0f, 50.0f);

	std::shared_ptr<namelessgui::ButtonGroup> spTerrainButtonGroup = std::make_shared<namelessgui::ButtonGroup>();
	namelessgui::RadioToggleButton* radioButton = new namelessgui::RadioToggleButton(spTerrainButtonGroup, "Wood");
	radioButton->setText("Wood");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, 5.0f});
	radioButton->setImage(TextureManager::getInstance()->getTexture("wood"));
	radioButton->signalActivated.connect(std::bind(&MapEditorState::slotTerrainButtonChanged, this, std::placeholders::_1));
	terrainWindow->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(spTerrainButtonGroup, "Hill");
	radioButton->setText("Hill");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, 1 * buttonSize.y + 5});
	radioButton->setImage(TextureManager::getInstance()->getTexture("hill"));
	radioButton->signalActivated.connect(std::bind(&MapEditorState::slotTerrainButtonChanged, this, std::placeholders::_1));
	terrainWindow->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(spTerrainButtonGroup, "Wall");
	radioButton->setText("Wall");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, 2 * buttonSize.y + 5});
	radioButton->setImage(TextureManager::getInstance()->getTexture("wall"));
	radioButton->signalActivated.connect(std::bind(&MapEditorState::slotTerrainButtonChanged, this, std::placeholders::_1));
	terrainWindow->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(spTerrainButtonGroup, "Erase");
	radioButton->setText("Erase");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, 3 * buttonSize.y + 5});
	radioButton->signalActivated.connect(std::bind(&MapEditorState::slotTerrainButtonChanged, this, std::placeholders::_1));
	terrainWindow->addWidget(radioButton);

	return terrainWindow;
}

} // namespace qrw
