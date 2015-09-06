#include "gamestates/mapeditorstate.hpp"

#include "gui/texturemanager.hpp"
#include "config/settings.hpp"
#include "engine/terrainfactory.hpp"

#include <iostream>

namespace qrw
{

MapEditorState::MapEditorState(sf::RenderWindow* renderWindow)
	: GameState(renderWindow, EGameStateId::EGSID_MAP_EDITOR_STATE),
	  _activeTerrainButton(nullptr)
{
	// Initialize background
	_background.setTexture(TextureManager::getInstance()->getTexture("plainsquare"));
	_background.setFillColor(sf::Color(255, 255, 255, 255));

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

	// Set up back to main menu dialog
	_backToMainMenuDialog = new namelessgui::ConfirmationDialog("Really exit and go back to main menu?");
	_backToMainMenuDialog->signalYesClicked.connect(std::bind(&MapEditorState::slotBackToMainMenu, this));
	_backToMainMenuDialog->setAnchor({0.5f, 0.5f});
	_backToMainMenuDialog->setParentAnchor({0.5f, 0.5f});
	_guiUptr->addWidget(_backToMainMenuDialog);

	// Set visibilities
	_guiUptr->setVisible(true);
	_background.setVisible(true);
	_backToMainMenuDialog->setVisible(false);

	// Handle cursor events
	_cursor.signalLeftClicked.connect(std::bind(&MapEditorState::slotCursorLeftClicked, this));
	_cursor.signalRightClicked.connect(std::bind(&MapEditorState::slotCursorRightClicked, this));
}

MapEditorState::~MapEditorState()
{
}

void MapEditorState::init(GameState* previousState)
{
	GameState::init();

	_backToMainMenu = false;
	_spBoard = std::make_shared<Board>(16, 9);

	_cursor.setBoard(_spBoard);

	sf::Vector2u spriteSize = _background.getTexture()->getSize();
	sf::Vector2f backgroundSize = sf::Vector2f(_spBoard->getWidth() * spriteSize.x, _spBoard->getHeight() * spriteSize.y);
	_background.setSize(backgroundSize);
}

EGameStateId MapEditorState::update()
{
	if(_backToMainMenu)
		return EGameStateId::EGSID_MAIN_MENU_STATE;

	return EGameStateId::EGSID_NO_CHANGE;
}

void MapEditorState::draw()
{
	_background.render(*_renderWindow, sf::RenderStates::Default);
	_renderWindow->draw(_cursor);
	_guiUptr->render(*_renderWindow, sf::RenderStates::Default);
}

bool MapEditorState::handleEvent(sf::Event& event)
{
	bool stopEventPropagation = GameState::handleEvent(event);

	if(stopEventPropagation)
		return stopEventPropagation;

	if(event.type == sf::Event::KeyPressed)
		if(event.key.code == sf::Keyboard::Escape)
			_backToMainMenuDialog->setVisible(true);

	// Scene must only handle events that are not consumed by the gui.
	if(!stopEventPropagation)
	{
		if(event.type == sf::Event::MouseMoved)
		{
			sf::Vector2i mousePixelCoordinates(event.mouseMove.x, event.mouseMove.y);

			sf::Vector2f mouseWorldCoordinates = _renderWindow->mapPixelToCoords(mousePixelCoordinates);

			sf::Event mouseMovedWorldCoordinates;
			mouseMovedWorldCoordinates.type = sf::Event::MouseMoved;
			mouseMovedWorldCoordinates.mouseMove.x = mouseWorldCoordinates.x;
			mouseMovedWorldCoordinates.mouseMove.y = mouseWorldCoordinates.y;

			_cursor.handleEvent(mouseMovedWorldCoordinates);
		}
		else
		{
			_cursor.handleEvent(event);
		}
	}

	return stopEventPropagation;
}

void MapEditorState::slotBackToMainMenu()
{
	_backToMainMenu = true;
}

void MapEditorState::slotCursorLeftClicked()
{
	std::cout << "Cursor left clicked.\n" << std::flush;
}

void MapEditorState::slotCursorRightClicked()
{
	std::cout << "Cursor right clicked.\n" << std::flush;
}

void MapEditorState::slotTerrainButtonChanged(namelessgui::RadioToggleButton* activeTerrainButton)
{
	_activeTerrainButton = activeTerrainButton;
}

} // namespace qrw
