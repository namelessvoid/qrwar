#include "gamestates/mapeditorstate.hpp"

#include "gui/texturemanager.hpp"
#include "config/settings.hpp"

#include <iostream>

namespace qrw
{

MapEditorState::MapEditorState(sf::RenderWindow* renderWindow)
	: GameState(renderWindow, EGameStateId::EGSID_MAP_EDITOR_STATE)
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

	namelessgui::Button* button = new namelessgui::Button();
	button->setText("Wood");
	button->setSize(buttonSize);
	button->setRelativePosition({5.0f, buttonSize.y});
	button->setImage(TextureManager::getInstance()->getTexture("wood"));
	_toolBar->addWidget(button);

	button = new namelessgui::Button();
	button->setText("Hill");
	button->setSize(buttonSize);
	button->setRelativePosition({5.0f, 2 * buttonSize.y});
	button->setImage(TextureManager::getInstance()->getTexture("hill"));
	_toolBar->addWidget(button);

	button = new namelessgui::Button();
	button->setText("Wall");
	button->setSize(buttonSize);
	button->setRelativePosition({5.0f, 3 * buttonSize.y});
	button->setImage(TextureManager::getInstance()->getTexture("wall"));
	_toolBar->addWidget(button);

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
}

MapEditorState::~MapEditorState()
{
}

void MapEditorState::init(GameState* previousState)
{
	GameState::init();

	_backToMainMenu = false;
	_spBoard = std::make_shared<Board>(16, 9);

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

	return stopEventPropagation;
}

void MapEditorState::slotBackToMainMenu()
{
	_backToMainMenu = true;
}

} // namespace qrw
