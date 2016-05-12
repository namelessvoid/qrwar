#include "gamestates/mapeditorstate.hpp"

#include "engine/terrain.hpp"
#include "engine/square.hpp"

#include "gui/texturemanager.hpp"

#include <iostream>

namespace qrw
{

MapEditorState::MapEditorState(sf::RenderWindow* renderWindow)
	: SceneState(renderWindow, EGameStateId::EGSID_MAP_EDITOR_STATE),
      _activeTerrainType(ET_NUMBEROFTERRAINTYPES),
      _eraseMode(false)
{
	// Initialize toolbar
	namelessgui::Label* label = new namelessgui::Label();
	label->setText("Terrain");
	label->setAnchor({0.5f, 0.0f});
	label->setParentAnchor({0.5f, 0.0f});
	_toolBar->addWidget(label);

	sf::Vector2f buttonSize(140.0f, 50.0f);

	namelessgui::RadioToggleButton* radioButton = new namelessgui::RadioToggleButton(nullptr, "Wood");
	std::shared_ptr<namelessgui::ButtonGroup> spTerrainButtonGroup = radioButton->getButtonGroup();
	radioButton->setText("Wood");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, buttonSize.y});
	radioButton->setImage(TextureManager::getInstance()->getTexture("wood"));
	radioButton->signalActivated.connect(std::bind(&MapEditorState::slotTerrainButtonChanged, this, std::placeholders::_1));
	_toolBar->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(spTerrainButtonGroup, "Hill");
	radioButton->setText("Hill");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, 2 * buttonSize.y});
	radioButton->setImage(TextureManager::getInstance()->getTexture("hill"));
	radioButton->signalActivated.connect(std::bind(&MapEditorState::slotTerrainButtonChanged, this, std::placeholders::_1));
	_toolBar->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(spTerrainButtonGroup, "Wall");
	radioButton->setText("Wall");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, 3 * buttonSize.y});
	radioButton->setImage(TextureManager::getInstance()->getTexture("wall"));
	radioButton->signalActivated.connect(std::bind(&MapEditorState::slotTerrainButtonChanged, this, std::placeholders::_1));
	_toolBar->addWidget(radioButton);

    radioButton = new namelessgui::RadioToggleButton(spTerrainButtonGroup, "Erase");
    radioButton->setText("Erase");
    radioButton->setSize(buttonSize);
    radioButton->setRelativePosition({5.0f, 4 * buttonSize.y});
    radioButton->signalActivated.connect(std::bind(&MapEditorState::slotTerrainButtonChanged, this, std::placeholders::_1));
    _toolBar->addWidget(radioButton);

	namelessgui::Button* toDeploymentButton = new namelessgui::Button();
	toDeploymentButton->setText("Deploy Troops");
	toDeploymentButton->setSize({buttonSize.x, 30.0f});
	toDeploymentButton->setAnchor({0.5f, 1.0f});
	toDeploymentButton->setParentAnchor({0.5f, 1.0f});
	toDeploymentButton->setRelativePosition({0.0f, -5.0f});
	toDeploymentButton->signalclicked.connect(std::bind(&MapEditorState::slotToDeploymentButtonClicked, this));
	_toolBar->addWidget(toDeploymentButton);
}

MapEditorState::~MapEditorState()
{
}

void MapEditorState::init(GameState* previousState)
{
	SceneState::init(previousState);

	_toDeployment = false;
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

Board::Ptr MapEditorState::getBoard() const
{
	return _spBoard;
}

void MapEditorState::slotCursorLeftClicked(const Coordinates& boardPosition)
{
    // Erase terrain
    if(_eraseMode)
    {
        Terrain::Ptr terrain = _spBoard->getSquare(boardPosition)->getTerrain();
        _spBoard->getSquare(boardPosition)->setTerrain(nullptr);
        _scene->removeTerrainEntityAt(boardPosition);
    }
    // Place terrain
    else
    {
        // Do nothing if no terrain type was selected and erase mode is off.
        if(_activeTerrainType == ET_NUMBEROFTERRAINTYPES)
            return;

        Terrain::Ptr terrain = Terrain::createTerrain(_activeTerrainType);
        if(terrain != nullptr)
        {
            _spBoard->getSquare(boardPosition)->setTerrain(terrain);
            _scene->addTerrainEntity(TerrainEntity::createTerrainEntity(terrain, 32));
        }
    }
}

void MapEditorState::slotCursorRightClicked(const Coordinates& boardPosition)
{
	_spBoard->getSquare(boardPosition)->setTerrain(nullptr);
	_scene->removeTerrainEntityAt(boardPosition);
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

void MapEditorState::slotToDeploymentButtonClicked()
{
	_toDeployment = true;
}

} // namespace qrw
