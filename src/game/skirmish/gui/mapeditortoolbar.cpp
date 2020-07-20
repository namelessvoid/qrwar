#include "game/skirmish/gui/mapeditortoolbar.hpp"

#include "gui/texturemanager.hpp"

#include "gui/ng/text.hpp"
#include "gui/ng/window.hpp"
#include "gui/ng/buttongroup.hpp"
#include "gui/ng/tabwidget.hpp"
#include "gui/ng/spinbox.hpp"
#include "gui/ng/lineinput.hpp"

namespace qrw
{

MapEditorToolBar::MapEditorToolBar(unsigned int initialBoardWidth, unsigned int initialBoardHeight)
	: namelessgui::TabWidget("MapEditorToolBar")
{
	TextureManager* textureManager = TextureManager::getInstance();

	setButtonSize({64, 64});
	addTab(textureManager->getTexture("wheel"), createConfigToolsWindow(initialBoardWidth, initialBoardHeight));
	addTab(textureManager->getTexture("wood"), createTerrainToolsWindow());
	addTab(textureManager->getTexture("mapeditor_structure"), createStructureToolsWindow());
	addTab(textureManager->getTexture("default"), createDeploymentZoneToolsWindow());
}

namelessgui::Window* MapEditorToolBar::createConfigToolsWindow(unsigned int initialBoardWidth, unsigned int initialBoardHeight)
{
	namelessgui::Window* configWindow = new namelessgui::Window("configToolsWindow");
	configWindow->setOutlineColor(configWindow->getFillColor());

	namelessgui::Text* heading = new namelessgui::Text();
	heading->setText("Settings");
	heading->setRelativePosition({5.0f, 0});
	configWindow->addWidget(heading);

	mapNameInput_ = new namelessgui::LineInput();
	mapNameInput_->setSize({252, 30});
	mapNameInput_->setText("Map Name");
	mapNameInput_->setRelativePosition({0, 50});
	configWindow->addWidget(mapNameInput_);

	namelessgui::Button* loadButton = new namelessgui::Button();
	loadButton->setText("Load");
	loadButton->setRelativePosition({0, 84});
	loadButton->setSize({124, 30});
	loadButton->signalClicked.connect([this] { signalLoadClicked.emit(mapNameInput_->getText()); });
	configWindow->addWidget(loadButton);

	namelessgui::Button* saveButton = new namelessgui::Button();
	saveButton->setText("Save");
	saveButton->setSize({124, 30.0f});
	saveButton->setRelativePosition({126.0f, 84.0f});
	saveButton->signalClicked.connect([this] () { signalSaveClicked.emit(mapNameInput_->getText()); });
	configWindow->addWidget(saveButton);

	namelessgui::SpinBox* mapWidthBox = new namelessgui::SpinBox();
	mapWidthBox->setSize({120.0f, 30.0f});
	mapWidthBox->setRelativePosition({0, 130});
	mapWidthBox->setMinValue(10);
	mapWidthBox->setMaxValue(128);
	mapWidthBox->setValue(initialBoardWidth);
	mapWidthBox->signalChanged.connect([this] (unsigned int width) { signalBoardWidthChanged.emit(width); });
	configWindow->addWidget(mapWidthBox);

	namelessgui::SpinBox* mapHeightBox = new namelessgui::SpinBox();
	mapHeightBox->setSize({120.0f, 30.0f});
	mapHeightBox->setRelativePosition({-8, 130});
	mapHeightBox->setMinValue(10);
	mapHeightBox->setMaxValue(128);
	mapHeightBox->setValue(initialBoardHeight);
	mapHeightBox->setAnchor({1, 0});
	mapHeightBox->setParentAnchor({1, 0});
	mapHeightBox->signalChanged.connect([this] (unsigned int height) { signalBoardHeightChanged.emit(height); });
	configWindow->addWidget(mapHeightBox);

	return configWindow;
}

namelessgui::Window* MapEditorToolBar::createTerrainToolsWindow()
{
	namelessgui::Window* terrainWindow = new namelessgui::Window("terrainToolsWindow");
	terrainWindow->setOutlineColor(terrainWindow->getFillColor());

	namelessgui::Text* heading = new namelessgui::Text();
	heading->setText("Terrain");
	heading->setRelativePosition({5.0f, 0});
	terrainWindow->addWidget(heading);

	std::shared_ptr<namelessgui::ButtonGroup> spTerrainButtonGroup = std::make_shared<namelessgui::ButtonGroup>();
	namelessgui::RadioToggleButton* radioButton = new namelessgui::RadioToggleButton(spTerrainButtonGroup, "Wood");
	radioButton->setText("Wood");
	radioButton->setSize(BUTTON_SIZE);
	radioButton->setRelativePosition({5.0f, BUTTON_Y_OFFSET});
	radioButton->setImage(TextureManager::getInstance()->getTexture("wood"));
	radioButton->signalActivated.connect([this] { signalTerrainTypeClicked.emit(TERRAINTYPES::ET_WOOD); });
	terrainWindow->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(spTerrainButtonGroup, "Hill");
	radioButton->setText("Hill");
	radioButton->setSize(BUTTON_SIZE);
	radioButton->setRelativePosition({5.0f, 1 * BUTTON_SIZE.y + BUTTON_Y_OFFSET});
	radioButton->setImage(TextureManager::getInstance()->getTexture("hill"));
	radioButton->signalActivated.connect([this] { signalTerrainTypeClicked.emit(TERRAINTYPES::ET_HILL); });
	terrainWindow->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(spTerrainButtonGroup, "Erase");
	radioButton->setText("Erase");
	radioButton->setSize(BUTTON_SIZE);
	radioButton->setRelativePosition({5.0f, 3 * BUTTON_SIZE.y + BUTTON_Y_OFFSET});
	radioButton->setImage(TextureManager::getInstance()->getTexture("default"));
	radioButton->signalActivated.connect([this] { signalEraseTerrainClicked.emit(); });
	terrainWindow->addWidget(radioButton);

	return terrainWindow;
}

namelessgui::Window* MapEditorToolBar::createStructureToolsWindow()
{
	namelessgui::Window* structureWindow = new namelessgui::Window("structureToolsWindow");
	structureWindow->setOutlineColor(structureWindow->getFillColor());

	namelessgui::Text* heading = new namelessgui::Text();
	heading->setText("Structures");
	heading->setRelativePosition({5.0f, 0});
	structureWindow->addWidget(heading);


	std::shared_ptr<namelessgui::ButtonGroup> structureButtonGroup = std::make_shared<namelessgui::ButtonGroup>();
	auto radioButton = new namelessgui::RadioToggleButton(structureButtonGroup, "Wall");
	radioButton->setText("Wall");
	radioButton->setSize(BUTTON_SIZE);
	radioButton->setRelativePosition({5.0f, 1 * BUTTON_SIZE.y + BUTTON_Y_OFFSET});
	radioButton->setImage(TextureManager::getInstance()->getTexture("wall"));
	radioButton->signalActivated.connect([this] { signalStructureClicked.emit(Structure::Type::WALL); });
	structureWindow->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(structureButtonGroup, "Stairs");
	radioButton->setText("Stairs");
	radioButton->setSize(BUTTON_SIZE);
	radioButton->setRelativePosition({5.0f, 2 * BUTTON_SIZE.y + BUTTON_Y_OFFSET});
	radioButton->setImage(TextureManager::getInstance()->getTexture("stairs"));
	radioButton->signalActivated.connect([this] { signalStructureClicked.emit(Structure::Type::STAIRS); });
	structureWindow->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(structureButtonGroup, "Erase");
	radioButton->setText("Erase");
	radioButton->setSize(BUTTON_SIZE);
	radioButton->setRelativePosition({5.0f, 3 * BUTTON_SIZE.y + BUTTON_Y_OFFSET});
	radioButton->setImage(TextureManager::getInstance()->getTexture("default"));
	radioButton->signalActivated.connect([this] { signalEraseStructureClicked.emit(); });
	structureWindow->addWidget(radioButton);

	return structureWindow;
}

namelessgui::Window* MapEditorToolBar::createDeploymentZoneToolsWindow()
{
	sf::Vector2f buttonSize(140.0f, 50.0f);
	float buttonYOffset = 45;

	namelessgui::Window* zoneWindow = new namelessgui::Window("deploymentZoneToolsWindow");
	zoneWindow->setOutlineColor(zoneWindow->getFillColor());

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
	radioButton->signalActivated.connect([this] { signalDeploymentZoneClicked.emit(0); });
	zoneWindow->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(zoneButtonGroup, "Player2");
	radioButton->setText("Player 2");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, 1 * buttonSize.y + buttonYOffset});
	radioButton->setImage(TextureManager::getInstance()->getTexture("default"));
	radioButton->signalActivated.connect([this] { signalDeploymentZoneClicked.emit(1); });
	zoneWindow->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(zoneButtonGroup, "Erase");
	radioButton->setText("Erase");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, 2 * buttonSize.y + buttonYOffset});
	radioButton->setImage(TextureManager::getInstance()->getTexture("default"));
	radioButton->signalActivated.connect([this] { signalEraseDeploymentZoneClicked.emit(); });
	zoneWindow->addWidget(radioButton);

	return zoneWindow;
}


}