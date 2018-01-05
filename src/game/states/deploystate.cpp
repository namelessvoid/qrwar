#include "game/states/deploystate.hpp"

#include <memory>
#include <cassert>

#include "engine/unit.hpp"

#include "game/states/skirmishpreparationstate.hpp"

#include "gui/texturemanager.hpp"

#include "gui/ng/radiotogglebutton.hpp"

#include "gui/cursor.hpp"

namespace qrw
{

DeployState::DeployState(sf::RenderWindow* renderWindow)
    : SceneState(renderWindow, EGameStateId::EGSID_DEPLOY_STATE),
      _toSkirmish(false)
{
	// Initialize tool bar
	sf::Vector2f buttonSize(140.0f, 50.0f);
	namelessgui::RadioToggleButton* radioButton = nullptr;
	std::shared_ptr<namelessgui::ButtonGroup> unitButtonGroup = nullptr;
	TextureManager* textureManager = TextureManager::getInstance();

	// Player one tools
	playerOneNameLabel_ = new namelessgui::Text();
	playerOneNameLabel_->setText("Player One");
	playerOneNameLabel_->setAnchor({0.5f, 0.0f});
	playerOneNameLabel_->setParentAnchor({0.5f, 0.0f});
	_toolBar->addWidget(playerOneNameLabel_);

	radioButton = new namelessgui::RadioToggleButton(nullptr, "p1swordman");
	unitButtonGroup = radioButton->getButtonGroup();
	radioButton->setText("Swordman");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, buttonSize.y});
	radioButton->setImage(textureManager->getTexture("p1swordman"));
	radioButton->signalActivated.connect(std::bind(&DeployState::slotUnitButtonChanged, this, std::placeholders::_1));
	_toolBar->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(unitButtonGroup, "p1archer");
	radioButton->setText("Archer");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, 2 * buttonSize.y});
	radioButton->setImage(textureManager->getTexture("p1archer"));
	radioButton->signalActivated.connect(std::bind(&DeployState::slotUnitButtonChanged, this, std::placeholders::_1));
	_toolBar->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(unitButtonGroup, "p1spearman");
	radioButton->setText("Spearman");
	radioButton->setSize(buttonSize);
	radioButton->setRelativePosition({5.0f, 3 * buttonSize.y});
	radioButton->setImage(textureManager->getTexture("p1spearman"));
	radioButton->signalActivated.connect(std::bind(&DeployState::slotUnitButtonChanged, this, std::placeholders::_1));
	_toolBar->addWidget(radioButton);

	// Player two tools
	playerTwoNameLabel_ = new namelessgui::Text();
	playerTwoNameLabel_->setText("Player Two");
	playerTwoNameLabel_->setAnchor({0.5f, 0.0f});
	playerTwoNameLabel_->setParentAnchor({0.5f, 0.4f});
	_toolBar->addWidget(playerTwoNameLabel_);

	radioButton = new namelessgui::RadioToggleButton(unitButtonGroup, "p2swordman");
	radioButton->setText("Swordman");
	radioButton->setSize(buttonSize);
	radioButton->setParentAnchor({0.0f, 0.4f});
	radioButton->setRelativePosition({5.0f, buttonSize.y});
	radioButton->setImage(textureManager->getTexture("p2swordman"));
	radioButton->signalActivated.connect(std::bind(&DeployState::slotUnitButtonChanged, this, std::placeholders::_1));
	_toolBar->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(unitButtonGroup, "p2archer");
	radioButton->setText("Archer");
	radioButton->setSize(buttonSize);
	radioButton->setParentAnchor({0.0f, 0.4f});
	radioButton->setRelativePosition({5.0f, 2 * buttonSize.y});
	radioButton->setImage(textureManager->getTexture("p2archer"));
	radioButton->signalActivated.connect(std::bind(&DeployState::slotUnitButtonChanged, this, std::placeholders::_1));
	_toolBar->addWidget(radioButton);

	radioButton = new namelessgui::RadioToggleButton(unitButtonGroup, "p2spearman");
	radioButton->setText("Spearman");
	radioButton->setSize(buttonSize);
	radioButton->setParentAnchor({0.0f, 0.4f});
	radioButton->setRelativePosition({5.0f, 3 * buttonSize.y});
	radioButton->setImage(textureManager->getTexture("p2spearman"));
	radioButton->signalActivated.connect(std::bind(&DeployState::slotUnitButtonChanged, this, std::placeholders::_1));
	_toolBar->addWidget(radioButton);

	// Next step button
	namelessgui::Button* nextStepButton = new namelessgui::Button();
	nextStepButton->setText("Into Battle");
	nextStepButton->setSize({buttonSize.x, 30.0f});
	nextStepButton->setAnchor({0.5f, 1.0f});
	nextStepButton->setParentAnchor({0.5f, 1.0f});
	nextStepButton->setRelativePosition({0.0f, -5.0f});
    nextStepButton->signalclicked.connect(std::bind(&DeployState::slotToSkirmishButtonClicked, this));
	_toolBar->addWidget(nextStepButton);
}

DeployState::~DeployState()
{

}

EGameStateId DeployState::update()
{
	if(_backToMainMenu)
		return EGameStateId::EGSID_MAIN_MENU_STATE;

	if(_toSkirmish)
		return EGameStateId::EGSID_SKIRMISH_STATE;

	return EGameStateId::EGSID_NO_CHANGE;
}

void DeployState::init(GameState* previousState)
{
	assert(previousState->getId() == EGameStateId::EGSID_SKIRMISH_PREPARATION_STATE);
	const SkirmishPreparationState* preparationState = static_cast<const SkirmishPreparationState*>(previousState);

	SceneState::init(previousState);

	// TODO: Load board from map file
	board_ = new Board(16, 9);
	g_scene.setBoard(board_);

	Cursor* cursor = new Cursor();
	g_scene.addGameObject(cursor);

	// Create new players
	_players.clear();
	_players.push_back(Player::Ptr(new Player()));
	_players[0]->setId(1);
	_players[0]->setName(preparationState->getPlayerOneName());
	_players.push_back(Player::Ptr(new Player()));
	_players[1]->setId(2);
	_players[1]->setName(preparationState->getPlayerTwoName());

	playerOneNameLabel_->setText(preparationState->getPlayerOneName());
	playerTwoNameLabel_->setText(preparationState->getPlayerTwoName());

    _toSkirmish = false;
}

Board* DeployState::getBoard() const
{
	return board_;
}

std::vector<Player::Ptr> DeployState::getPlayers() const
{
    return _players;
}

void DeployState::slotUnitButtonChanged(const namelessgui::RadioToggleButton& unitButton)
{
	std::string buttonId = unitButton.getId();
	std::string unitName = buttonId.substr(2);

	// Determine player id
	_selectedPlayer = _players.at(buttonId.at(1) - 49);

	// Determine unit type
	if(unitName == "swordman")
		_selectedUnitType = EUT_SWORDMAN;
	else if(unitName == "archer")
		_selectedUnitType = EUT_ARCHER;
	else if(unitName == "spearman")
        _selectedUnitType = EUT_SPEARMAN;
}

void DeployState::slotToSkirmishButtonClicked()
{
    _toSkirmish = true;
}

void DeployState::slotCursorLeftClicked(const Coordinates& boardPosition)
{
	if(_selectedPlayer == nullptr)
		return;

	if(Unit* unit = board_->getUnit(boardPosition))
		g_scene.despawn(unit);

	Unit* unit = Unit::createUnit(_selectedUnitType, _selectedPlayer);
	unit->setPosition(boardPosition);
	g_scene.addGameObject(unit);
}

void DeployState::slotCursorRightClicked(const Coordinates &boardPosition)
{
	if(Unit* unit = board_->getUnit(boardPosition))
		g_scene.despawn(unit);
}

} // namespace qrw
