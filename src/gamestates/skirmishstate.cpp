#include "gamestates/skirmishstate.hpp"

#include "gamestates/deploystate.hpp"
#include "engine/square.hpp"
#include "engine/pathfinding/astar.hpp"
#include "engine/pathfinding/path.hpp"
#include "gui/texturemanager.hpp"
#include "gui/ng/label.hpp"
#include "gui/ng/spritewidget.hpp"
#include "gui/ng/button.hpp"
#include "gui/squaredetailwindow.hpp"

#include <iostream>

namespace qrw
{

SkirmishState::SkirmishState(sf::RenderWindow* renderWindow)
	: SceneState(renderWindow, EGameStateId::EGSID_SKIRMISH_STATE),
	  _pathFinder(new AStar())
{
    _squareDetailWindow = new SquareDetailWindow();
    _guiUptr->addWidget(_squareDetailWindow);

	_playerNameText = new namelessgui::Text();
	_playerNameText->setText("Player Name");
	_playerNameText->setParentAnchor({0.5, 0});
	_playerNameText->setAnchor({0.5, 0});
	_toolBar->addWidget(_playerNameText);

	namelessgui::Button* endTurnButton = new namelessgui::Button();
	endTurnButton->setText("End Turn");
	endTurnButton->setSize({140, 30});
	endTurnButton->setParentAnchor({0.5, 1});
	endTurnButton->setAnchor({0.5, 1.0});
	endTurnButton->setRelativePosition({0.0f, -5.0f});
	endTurnButton->signalclicked.connect(std::bind(&SkirmishState::endTurn, this));
	_toolBar->addWidget(endTurnButton);
}

void SkirmishState::init(GameState *previousState)
{
    SceneState::init(previousState);

    if(previousState->getId() != EGameStateId::EGSID_DEPLOY_STATE)
        return;

    DeployState* deployState = static_cast<DeployState*>(previousState);

    _board = deployState->getBoard();
    _scene->setBoard(_board);
	_pathFinder->setBoard(_board.get());

	_players = deployState->getPlayers();
	_currentPlayer = 0;
	_playerNameText->setText(_players[_currentPlayer]->getName());

    // Initialize square detail window.
    Coordinates cursorPosition = _scene->getCursorPosition();
    if(_board->isOnBoard(cursorPosition))
        _squareDetailWindow->setSquare(_board->getSquare(cursorPosition));
}

EGameStateId SkirmishState::update()
{
    if(_backToMainMenu)
        return EGameStateId::EGSID_MAIN_MENU_STATE;

    return EGameStateId::EGSID_NO_CHANGE;
}

void SkirmishState::slotCursorMoved(const Coordinates &boardPosition, bool isOnBoard)
{
    if(isOnBoard)
	{
        _squareDetailWindow->setSquare(_board->getSquare(boardPosition));
		if(_selectedUnit)
			_path.reset(_pathFinder->findPath({0, 0}, boardPosition));
	}
    else
        _squareDetailWindow->setSquare(nullptr);
}

void SkirmishState::slotCursorLeftClicked(const Coordinates &boardPosition)
{
	Square* square = _board->getSquare(boardPosition);
	_selectedUnit = square->getUnit();

	// Do not allow to select units of other player
	if(_selectedUnit && _selectedUnit->getPlayer() != _players[_currentPlayer])
		_selectedUnit = nullptr;
}

void SkirmishState::endTurn()
{
	_currentPlayer = (_currentPlayer + 1) % _players.size();
	_playerNameText->setText(_players[_currentPlayer]->getName());
	_selectedUnit = nullptr;
}

} // namespace qrw
