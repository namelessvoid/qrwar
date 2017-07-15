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

#include <SFML/Graphics/Sprite.hpp>

#include <iostream>
#include <memory>

namespace qrw
{

SkirmishState::SkirmishState(sf::RenderWindow* renderWindow)
	: SceneState(renderWindow, EGameStateId::EGSID_SKIRMISH_STATE),
	  _squareMarker(new SquareMarker())
{
    _squareDetailWindow = new SquareDetailWindow();
    _guiUptr->addWidget(_squareDetailWindow);

	_squareMarker->setVisible(false);

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

	_players = deployState->getPlayers();
	_currentPlayer = 0;
	_playerNameText->setText(_players[_currentPlayer]->getName());

    // Initialize square detail window.
    Coordinates cursorPosition = _scene->getCursorPosition();
    if(_board->isOnBoard(cursorPosition))
		_squareDetailWindow->setSquare(_board->getSquare(cursorPosition));
}

void SkirmishState::draw()
{
	SceneState::draw();
	_squareMarker->draw(*_renderWindow, sf::RenderStates::Default);
	drawPath();
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
			_path.reset(_board->findPath(_selectedUnit->getPosition(), boardPosition));
	}
    else
        _squareDetailWindow->setSquare(nullptr);
}

void SkirmishState::moveUnit()
{
	if(!_selectedUnit) return;
	if(!_path) return;

	int pathCosts = _path->getMovementCosts();
	if(pathCosts == 0) return;

	int maxDistance = _selectedUnit->getCurrentMovement();
	if(pathCosts > maxDistance) return;

	int remainingMovement = maxDistance - pathCosts;
	_selectedUnit->setCurrentMovement(remainingMovement);

	_board->getSquare(_squareMarker->getBoardPosition())->setUnit(nullptr);
	_board->getSquare(_path->getTargetPosition())->setUnit(_selectedUnit);

	deselectUnit();

	std::cout << "Move unit." << std::endl;
}

void SkirmishState::performAttack()
{
	std::cout << "Attack unit." << std::endl;
}

void SkirmishState::slotCursorLeftClicked(const Coordinates &boardPosition)
{
	// Case 1: Unit is selected and instructed to attack enemy unit
	Square* squareUnderCursor = _board->getSquare(boardPosition);
	Unit::Ptr unitUnderCursor = squareUnderCursor->getUnit();

	if(_selectedUnit && !unitUnderCursor)
	{
		// Move unit
		moveUnit();
		return;
	}

	if(_selectedUnit && unitUnderCursor && unitUnderCursor->getPlayer() != _selectedUnit->getPlayer())
	{
		performAttack();
		return;
	}

	// Do not allow to select units of other player
	if(unitUnderCursor && unitUnderCursor->getPlayer() != _players[_currentPlayer])
	{
		// Select unit
		_selectedUnit = unitUnderCursor;
		_squareMarker->setBoardPosition(boardPosition);
		_squareMarker->setVisible(true);

		return;
	}

	deselectUnit();
}

bool SkirmishState::handleEvent(sf::Event& event)
{
	bool stopEventPropagation = SceneState::handleEvent(event);

	if(stopEventPropagation)
		return stopEventPropagation;

	if(event.type == sf::Event::MouseButtonReleased)
	{
		if(event.mouseButton.button == sf::Mouse::Right)
		{
			deselectUnit();
			return true;
		}
	}

	return stopEventPropagation;
}

void SkirmishState::endTurn()
{
	_currentPlayer = (_currentPlayer + 1) % _players.size();
	_playerNameText->setText(_players[_currentPlayer]->getName());

	deselectUnit();
}

void SkirmishState::drawPath()
{
	if(!_path)
		return;

	const int pathLength = _path->getLength();

	Square* previous = 0;
	Square* current  = _path->getStep(0);
	Square* next     = _path->getStep(1);

	sf::Sprite footstep = sf::Sprite(*TextureManager::getInstance()->getTexture("footstep"));

	// Do not render first step.
	for(int i = 1; i < pathLength; ++i)
	{
		previous = current;
		current  = next;

		// Reset the previously applied transformations.
		footstep.setOrigin(16, 16);
		footstep.setScale(1, 1);
		footstep.setRotation(0);

		// Transformations relative to the previous step
		Coordinates prevDelta(previous->getCoordinates() - current->getCoordinates());
		if(prevDelta.getX() != 0)
			footstep.rotate(-90 * prevDelta.getX());
		if(prevDelta.getY() != 0)
			footstep.scale(1, prevDelta.getY());

		// Transformations relative to the next step (if possible)
		if(i < pathLength - 1)
		{
			next = _path->getStep(i+1);

			Coordinates prevNextDelta(previous->getCoordinates() - next->getCoordinates());

			// If the path has a corner at this position
			if(prevNextDelta.getX() != 0 && prevNextDelta.getY() != 0)
			{
				int rotationdirection = 0;
				// horizontal
				if(prevDelta.getX() == 0)
				{
					rotationdirection = -1;
				}
				// vertical
				else if(prevDelta.getY() == 0)
				{
					rotationdirection = +1;
				}
				footstep.rotate(rotationdirection * 45 * (prevNextDelta.getX() * prevNextDelta.getY()));
			}
		}

		footstep.setPosition(
			32 * (0.5f + current->getXPosition()),
			32 * (0.5f + current->getYPosition())
		);

		_renderWindow->draw(footstep);
	}
}

void SkirmishState::deselectUnit()
{
	_selectedUnit = nullptr;
	_squareMarker->setVisible(false);
	_path.reset();
}

} // namespace qrw
