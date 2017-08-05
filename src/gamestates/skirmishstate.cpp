#include "gamestates/skirmishstate.hpp"

#include "gamestates/deploystate.hpp"
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
	g_scene.setBoard(_board);

	_players = deployState->getPlayers();
	_currentPlayer = 0;
	_playerNameText->setText(_players[_currentPlayer]->getName());

    // Initialize square detail window.
	Coordinates cursorPosition = g_scene.getCursorPosition();
	Unit::Ptr unit = _board->getUnit(cursorPosition);
	Terrain::Ptr terrain = _board->getTerrain(cursorPosition);
	_squareDetailWindow->setUnitAndTerrain(unit, terrain);
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

void SkirmishState::slotCursorMoved(const Coordinates &boardPosition)
{
	if(_board->isOnBoard(boardPosition))
	{
		Unit::Ptr unitUnderCursor = _board->getUnit(boardPosition);
		Terrain::Ptr terrainUnderCursor = _board->getTerrain(boardPosition);
		_squareDetailWindow->setUnitAndTerrain(unitUnderCursor, terrainUnderCursor);

		if(_selectedUnit)
		{
			_path.reset(_board->findPath(_selectedUnit->getPosition(), boardPosition));

			Cursor::Color cursorColor = Cursor::Color::ESC_DEFAULT;
			if(!_path || _path->getMovementCosts() > _selectedUnit->getCurrentMovement())
				cursorColor = Cursor::Color::ESC_WARNING;
			if(boardPosition == _squareMarker->getBoardPosition())
				cursorColor = Cursor::Color::ESC_DEFAULT;

			g_scene.getCursor().setFillColor(cursorColor);
		}
	}
    else
		_squareDetailWindow->setUnitAndTerrain(nullptr, nullptr);
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

	_board->moveUnit(_squareMarker->getBoardPosition(), _path->getTarget());
	_selectedUnit->setPosition(_path->getTarget());

	std::cout << "Move unit." << std::endl;
}

void SkirmishState::performAttack(std::shared_ptr<Unit> attackedUnit)
{
	const Coordinates& positionOfAttackedUnit = attackedUnit->getPosition();

	if(!_selectedUnit->isTargetWithinAttackRange(positionOfAttackedUnit))
		return;

	if(_selectedUnit->getCurrentMovement() == 0)
		return;
	_selectedUnit->setCurrentMovement(0);

	int inflictedDamage = _selectedUnit->getModifiedAttack() - attackedUnit->getModifiedDefense();
	inflictedDamage = inflictedDamage < 0 ? 0 : inflictedDamage;
	attackedUnit->damage(inflictedDamage);

	if(attackedUnit->getHP() == 0)
	{
		_board->removeUnit(positionOfAttackedUnit);
		_board->moveUnit(_selectedUnit->getPosition(), positionOfAttackedUnit);
		_selectedUnit->setPosition(positionOfAttackedUnit);
	}
	else
	{
		inflictedDamage = attackedUnit->getModifiedAttack() - _selectedUnit->getModifiedDefense();
		inflictedDamage = inflictedDamage < 0 ? 0 : inflictedDamage;
		_selectedUnit->damage(inflictedDamage);

		if(_selectedUnit->getHP() == 0)
		{
			_board->removeUnit(_selectedUnit->getPosition());
		}
	}

	updateSquareDetailWindow(positionOfAttackedUnit);

	std::cout << "Attack unit." << std::endl;
}

void SkirmishState::replenishTroops()
{
	Unit* unit;
	for(auto unitIter : _board->getUnits())
	{
		unit = unitIter.second.get();
		unit->setCurrentMovement(unit->getMovement());
	}
}

void SkirmishState::updateSquareDetailWindow(const Coordinates& position)
{
	_squareDetailWindow->setUnitAndTerrain(
				_board->getUnit(position),
				_board->getTerrain(position));
}

void SkirmishState::slotCursorLeftClicked(const Coordinates &boardPosition)
{
	Unit::Ptr unitUnderCursor = _board->getUnit(boardPosition);
	Terrain::Ptr terrainUnderCursor = _board->getTerrain(boardPosition);

	_squareDetailWindow->setUnitAndTerrain(unitUnderCursor, terrainUnderCursor);

	// Case 1: Unit is selected and instructed to move.
	if(_selectedUnit && !unitUnderCursor)
	{
		moveUnit();
		deselectUnit();
		return;
	}

	// Case 2: Unit is selected and instructed to attack enemy.
	if(_selectedUnit && unitUnderCursor && unitUnderCursor->getPlayer() != _selectedUnit->getPlayer())
	{
		performAttack(unitUnderCursor);
		deselectUnit();
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
	if(SceneState::handleEvent(event))
		return true;

	if(event.type == sf::Event::MouseButtonReleased)
	{
		if(event.mouseButton.button == sf::Mouse::Right)
		{
			deselectUnit();
			return true;
		}
	}

	return false;
}

void SkirmishState::endTurn()
{
	_currentPlayer = (_currentPlayer + 1) % _players.size();
	_playerNameText->setText(_players[_currentPlayer]->getName());

	deselectUnit();
	replenishTroops();
}

void SkirmishState::drawPath()
{
	if(!_path)
		return;

	const int pathLength = _path->getLength();

	const Coordinates* previous = nullptr;
	const Coordinates* current  = &_path->getStep(0);
	const Coordinates* next     = &_path->getStep(1);

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
		Coordinates prevDelta(*previous - *current);
		if(prevDelta.getX() != 0)
			footstep.rotate(-90 * prevDelta.getX());
		if(prevDelta.getY() != 0)
			footstep.scale(1, prevDelta.getY());

		// Transformations relative to the next step (if possible)
		if(i < pathLength - 1)
		{
			next = &_path->getStep(i+1);

			Coordinates prevNextDelta(*previous - *next);

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
			32 * (0.5f + current->getX()),
			32 * (0.5f + current->getY())
		);

		_renderWindow->draw(footstep);
	}
}

void SkirmishState::deselectUnit()
{
	_selectedUnit = nullptr;
	_squareMarker->setVisible(false);
	g_scene.getCursor().setFillColor(Cursor::Color::ESC_DEFAULT);
	_path.reset();
}

} // namespace qrw
