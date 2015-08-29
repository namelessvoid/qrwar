#include "gamestates/mapeditorstate.hpp"

#include "gui/texturemanager.hpp"

#include <iostream>

namespace qrw
{

MapEditorState::MapEditorState(sf::RenderWindow* renderWindow)
	: GameState(renderWindow, EGameStateId::EGSID_MAP_EDITOR_STATE),
	  _backToMainMenuDialog("Really exit and go back to main menu?")
{
	_backToMainMenuDialog.signalYesClicked.connect(std::bind(&MapEditorState::slotBackToMainMenu, this));
	_background.setVisible(true);
}

void MapEditorState::init(GameState* previousState)
{
	_backToMainMenu = false;
	_spBoard = std::make_shared<Board>(16, 9);

	_background.setTexture(TextureManager::getInstance()->getTexture("plainsquare"));
	sf::Vector2u spriteSize = _background.getTexture()->getSize();
	sf::Vector2f backgroundSize = sf::Vector2f(_spBoard->getWidth() * spriteSize.x, _spBoard->getHeight() * spriteSize.y);
	_background.setSize(backgroundSize);
	_background.setFillColor(sf::Color(255, 255, 255, 255));
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

	_backToMainMenuDialog.render(*_renderWindow, sf::RenderStates::Default);
}

void MapEditorState::handleEvent(sf::Event& event)
{
	GameState::handleEvent(event);

	if(_backToMainMenuDialog.isVisible())
	{
		_backToMainMenuDialog.handleEvent(event);
		return;
	}

	if(event.type == sf::Event::KeyPressed)
		if(event.key.code == sf::Keyboard::Escape)
			_backToMainMenuDialog.setVisible(true);
}

void MapEditorState::slotBackToMainMenu()
{
	_backToMainMenu = true;
}

} // namespace qrw
