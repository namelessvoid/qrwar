#include "game/states/skirmishstate.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include "game/skirmish/gui/victorydialog.hpp"
#include "game/skirmish/gui/squaredetailwindow.hpp"
#include "game/states/deploystate.hpp"
#include "game/path.hpp"

#include "engine/pathfinding/astar.hpp"
#include "engine/pathfinding/path.hpp"
#include "engine/player.hpp"

#include "gui/texturemanager.hpp"
#include "gui/ng/label.hpp"
#include "gui/ng/spritewidget.hpp"
#include "gui/ng/button.hpp"
#include "gui/cursor.hpp"
#include "gui/squaremarker.hpp"

#include "eventsystem/inputevents.hpp"

namespace qrw
{

SkirmishState::SkirmishState(sf::RenderWindow* renderWindow)
	: SceneState(renderWindow, EGameStateId::EGSID_SKIRMISH_STATE),
	  _selectedUnit(nullptr),
	  m_victoryGui(new namelessgui::Gui(renderWindow))
{
    _squareDetailWindow = new SquareDetailWindow();
    _guiUptr->addWidget(_squareDetailWindow);

	path_ = new Path();
	g_scene.addGameObject(path_);

	_squareMarker = new SquareMarker();
	_squareMarker->setVisible(false);
	g_scene.addGameObject(_squareMarker);

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
	endTurnButton->signalClicked.connect(std::bind(&SkirmishState::endTurn, this));
	_toolBar->addWidget(endTurnButton);

	m_victoryDialog = new VictoryDialog();
	m_victoryDialog->signalCloseClicked.connect(std::bind(&SceneState::slotBackToMainMenu, this));
	m_victoryGui->addWidget(m_victoryDialog);
	m_victoryGui->setVisible(false);
}

void SkirmishState::init(GameState *previousState)
{
    SceneState::init(previousState);

	assert(previousState->getId() == EGameStateId::EGSID_DEPLOY_STATE);

    DeployState* deployState = static_cast<DeployState*>(previousState);

    _board = deployState->getBoard();
	g_scene.setBoard(_board);

	_players = deployState->getPlayers();
	_currentPlayer = 0;
	_playerNameText->setText(_players[_currentPlayer]->getName());

    // Initialize square detail window.
	const Coordinates& cursorPosition = g_scene.findSingleGameObject<Cursor>()->getBoardPosition();
	Unit* unit = _board->getUnit(cursorPosition);
	Terrain* terrain = _board->getTerrain(cursorPosition);
	_squareDetailWindow->setUnitAndTerrain(unit, terrain);
}

void SkirmishState::draw()
{
	SceneState::draw();
	m_victoryGui->render(*_renderWindow);
}

bool SkirmishState::handleEvent(const IEvent &event)
{
	SceneState::handleEvent(event);

	if(event.getName() == RightMouseButtonPressedEvent::name)
		deselectUnit();

	return false;
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
		Unit* unitUnderCursor = _board->getUnit(boardPosition);
		Terrain* terrainUnderCursor = _board->getTerrain(boardPosition);
		_squareDetailWindow->setUnitAndTerrain(unitUnderCursor, terrainUnderCursor);

		if(_selectedUnit)
		{
			path_->setStartAndEnd(_selectedUnit->getPosition(), boardPosition);

			Cursor* cursor = g_scene.findSingleGameObject<Cursor>();

			if(_selectedUnit && unitUnderCursor && unitUnderCursor->getPlayer() != _selectedUnit->getPlayer()
			   && _selectedUnit->getCurrentMovement() > 0
			   && _selectedUnit->getPosition().distanceTo(boardPosition) <= _selectedUnit->getAttackRange())
			{
				cursor->markAttackable();
			}
			else if(path_->getMovementCosts() > _selectedUnit->getCurrentMovement())
				cursor->markInvalid();
			else
				cursor->markValid();
			
		}
	}
    else
		_squareDetailWindow->setUnitAndTerrain(nullptr, nullptr);
}

void SkirmishState::moveUnit()
{
	if(!_selectedUnit) return;

	int pathCosts = path_->getMovementCosts();

	int maxDistance = _selectedUnit->getCurrentMovement();
	if(pathCosts > maxDistance) return;

	int remainingMovement = maxDistance - pathCosts;
	_selectedUnit->setCurrentMovement(remainingMovement);
	_selectedUnit->move(*path_);
}

void SkirmishState::performAttack(Unit* attackedUnit)
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
		g_scene.destroy(attackedUnit);
		_selectedUnit->setPosition(positionOfAttackedUnit);
	}
	else
	{
		inflictedDamage = attackedUnit->getModifiedAttack() - _selectedUnit->getModifiedDefense();
		inflictedDamage = inflictedDamage < 0 ? 0 : inflictedDamage;
		_selectedUnit->damage(inflictedDamage);

		if(_selectedUnit->getHP() == 0)
		{
			g_scene.destroy(_selectedUnit);
			_selectedUnit = nullptr;
		}
	}

	updateSquareDetailWindow(positionOfAttackedUnit);
}

void SkirmishState::checkVictory()
{
	bool playersHaveUnits[] = {false, false};

	for(auto unitIter : _board->getUnits())
	{
		playersHaveUnits[unitIter.second->getPlayer()->getId() - 1] = true;
	}

	bool gameEnded = !playersHaveUnits[0] || !playersHaveUnits[1];
	if(gameEnded)
	{
		m_victoryDialog->setLoserName(!playersHaveUnits[0] ? _players[0]->getName() : _players[1]->getName());
		m_victoryDialog->setWinnerName(!playersHaveUnits[0] ? _players[1]->getName() : _players[0]->getName());
		m_victoryGui->setVisible(true);
		_guiUptr->setVisible(false);
	}
}

void SkirmishState::replenishTroops()
{
	Unit* unit;
	for(auto unitIter : _board->getUnits())
	{
		unit = unitIter.second;
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
	Unit* unitUnderCursor = _board->getUnit(boardPosition);
	Terrain* terrainUnderCursor = _board->getTerrain(boardPosition);

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
		checkVictory();
		return;
	}

	// Select unit if it belongs to current player
	if(unitUnderCursor && unitUnderCursor->getPlayer() == _players[_currentPlayer])
	{
		// Select unit
		_selectedUnit = unitUnderCursor;
		_squareMarker->setBoardPosition(boardPosition);
		_squareMarker->setVisible(true);

		return;
	}

	deselectUnit();
}

void SkirmishState::endTurn()
{
	_currentPlayer = (_currentPlayer + 1) % _players.size();
	_playerNameText->setText(_players[_currentPlayer]->getName());

	deselectUnit();
	replenishTroops();
}

void SkirmishState::deselectUnit()
{
	_selectedUnit = nullptr;
	_squareMarker->setVisible(false);
	g_scene.findSingleGameObject<Cursor>()->markValid();
	path_->reset();
}

} // namespace qrw
