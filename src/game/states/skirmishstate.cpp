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
	  toggleFlatModeHandler_(),
	  _selectedUnit(nullptr),
	  m_victoryGui(new namelessgui::Gui(renderWindow))
{
    _squareDetailWindow = new SquareDetailWindow();
    _guiUptr->addWidget(_squareDetailWindow);

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
	_squareDetailWindow->display(cursorPosition, *_board, *_players[_currentPlayer]);
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
		deselectSquare();

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
	bool isAbilityApplicable = false;
	if(UnitAbility* selectedAbility = _squareDetailWindow->getSelectedUnitAbility())
	{
		selectedAbility->activate();
		selectedAbility->updateActiveVisualization(boardPosition);
		isAbilityApplicable = selectedAbility->canBeExecutedOn(boardPosition);
	}
	else if(_board->isOnBoard(boardPosition) && _selectedUnit)
	{
		UnitAbility* ability = _selectedUnit->updateAbilitiesToTarget(boardPosition);
		isAbilityApplicable = ability != nullptr;
	}

	Cursor* cursor = g_scene.findSingleGameObject<Cursor>();
	if(!_selectedUnit || isAbilityApplicable) cursor->markValid();
	else cursor->markInvalid();
}

void SkirmishState::slotCursorLeftClicked(const Coordinates& boardPosition)
{
	Unit* unitUnderCursor = _board->getUnit(boardPosition);

	if(_selectedUnit)
	{
		bool abilityExecuted = false;

		if(UnitAbility* selectedAbility = _squareDetailWindow->getSelectedUnitAbility())
		{
			if(selectedAbility->canBeExecutedOn(boardPosition))
			{
				selectedAbility->executeOn(boardPosition);
				abilityExecuted = true;
			}
		}
		else
		{
			abilityExecuted = _selectedUnit->tryExecuteAbility(boardPosition);
		}

		_squareMarker->setBoardPosition(_selectedUnit->getPosition());

		if(_selectedUnit->getCurrentHp() == 0)
			deselectSquare();

		if(abilityExecuted)
			checkVictory();
	}

	if(unitUnderCursor && unitUnderCursor->getPlayer() == _players[_currentPlayer])
	{
		// Select unit
		_selectedUnit = unitUnderCursor;
		_squareMarker->setBoardPosition(boardPosition);
		_squareMarker->setVisible(true);
	}

	if(_selectedUnit)
		_squareDetailWindow->display(_selectedUnit->getPosition(), *_board, *_players[_currentPlayer]);
	else
		_squareDetailWindow->display(boardPosition, *_board, *_players[_currentPlayer]);
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

void SkirmishState::endTurn()
{
	_currentPlayer = (_currentPlayer + 1) % _players.size();
	_playerNameText->setText(_players[_currentPlayer]->getName());

	deselectSquare();
	replenishTroops();
}

void SkirmishState::deselectSquare()
{
	if(_selectedUnit) _selectedUnit->deactivateAllAbilities();

	_selectedUnit = nullptr;
	_squareMarker->setVisible(false);
	g_scene.findSingleGameObject<Cursor>()->markValid();
	_squareDetailWindow->clear();
}

} // namespace qrw
