#include "gamestates/mapeditorstate.hpp"

#include "gui/texturemanager.hpp"
#include "config/settings.hpp"

#include <iostream>

namespace qrw
{

MapEditorState::MapEditorState(sf::RenderWindow* renderWindow)
	: GameState(renderWindow, EGameStateId::EGSID_MAP_EDITOR_STATE),
	  _menusInitialized(false)
{
	_backToMainMenuDialog = new namelessgui::ConfirmationDialog("Really exit and go back to main menu?");
	_backToMainMenuDialog->signalYesClicked.connect(std::bind(&MapEditorState::slotBackToMainMenu, this));

	// Initialize toolbar
	_toolBar.setVisible(true);
	_toolBar.setSize({150.0f, (float)Settings::getInstance()->getResolutionY()});
	_toolBar.setPosition({
		 (float)Settings::getInstance()->getResolutionX() - _toolBar.getSize().x,
		 0.0f
	});
	_toolBar.setVisible(true);

	namelessgui::Label* label = new namelessgui::Label();
	label->setText("Terrain");
	label->setAnchor({0.5f, 0.0f});
	label->setParentAnchor({0.5f, 0.0f});
	_toolBar.addWidget(label);

	_guiUptr->addWidget(_backToMainMenuDialog);

	// Render background
	_background.setVisible(true);
	_guiUptr->setVisible(true);
	_backToMainMenuDialog->setVisible(false);
}

MapEditorState::~MapEditorState()
{
}

void MapEditorState::init(GameState* previousState)
{
	// Initial setup that only needs to be done once.
	if(!_menusInitialized)
	{
		_background.setTexture(TextureManager::getInstance()->getTexture("plainsquare"));
		_background.setFillColor(sf::Color(255, 255, 255, 255));

		namelessgui::Button* button = new namelessgui::Button();
		button->setText("Wood");
		button->setSize({140.0f, 50.0f});
		button->setRelativePosition({5.0f, 50.0f});
		button->setImage(TextureManager::getInstance()->getTexture("wood"));
		_toolBar.addWidget(button);

		_menusInitialized = true;
	}

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
	_toolBar.render(*_renderWindow, sf::RenderStates::Default);

	_guiUptr->render(*_renderWindow, sf::RenderStates::Default);
}

void MapEditorState::handleEvent(sf::Event& event)
{
	GameState::handleEvent(event);

	if(event.type == sf::Event::KeyPressed)
		if(event.key.code == sf::Keyboard::Escape)
			_backToMainMenuDialog->setVisible(true);

	_guiUptr->handleEvent(event);
	_toolBar.handleEvent(event);
}

void MapEditorState::slotBackToMainMenu()
{
	_backToMainMenu = true;
}

} // namespace qrw
