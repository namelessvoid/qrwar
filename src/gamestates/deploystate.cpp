#include "gamestates/deploystate.hpp"

#include <memory>

#include "gamestates/mapeditorstate.hpp"

#include "gui/texturemanager.hpp"

#include "gui/ng/radiotogglebutton.hpp"

namespace qrw
{

DeployState::DeployState(sf::RenderWindow* renderWindow)
	: SceneState(renderWindow, EGameStateId::EGSID_DEPLOY_STATE)
{
	// Initialize tool bar
	sf::Vector2f buttonSize(140.0f, 50.0f);
	namelessgui::RadioToggleButton* radioButton = nullptr;
	namelessgui::Label* label = nullptr;
	std::shared_ptr<namelessgui::ButtonGroup> unitButtonGroup = nullptr;
	TextureManager* textureManager = TextureManager::getInstance();

	// Player one tools
	label = new namelessgui::Label();
	label->setText("Player One");
	label->setAnchor({0.5f, 0.0f});
	label->setParentAnchor({0.5f, 0.0f});
	_toolBar->addWidget(label);

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
	label = new namelessgui::Label();
	label->setText("Player Two");
	label->setAnchor({0.5f, 0.0f});
	label->setParentAnchor({0.5f, 0.4f});
	_toolBar->addWidget(label);

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
	_toolBar->addWidget(nextStepButton);
}

DeployState::~DeployState()
{

}

EGameStateId DeployState::update()
{
	if(_backToMainMenu)
		return EGameStateId::EGSID_MAIN_MENU_STATE;

	return EGameStateId::EGSID_NO_CHANGE;
}

void DeployState::init(GameState* previousState)
{
	SceneState::init(previousState);

	if(previousState->getId() == EGameStateId::EGSID_MAP_EDITOR_STATE)
	{
		_board = static_cast<MapEditorState*>(previousState)->getBoard();
		_scene = std::unique_ptr<Scene>(new Scene(_renderWindow, _board));
	}

	// Create new players
	_players.clear();
	_players.push_back(Player::Ptr(new Player()));
	_players.push_back(Player::Ptr(new Player()));
}

void DeployState::slotUnitButtonChanged(const namelessgui::RadioToggleButton& unitButton)
{
	std::string buttonId = unitButton.getId();
	std::string unitName = buttonId.substr(2);

	// Determine player id
	_selectedPlayer = buttonId.at(1) - 49;

	// Determine unit type
	if(unitName == "swordman")
		_selectedUnitType = EUT_SWORDMAN;
	else if(unitName == "archer")
		_selectedUnitType = EUT_ARCHER;
	else if(unitName == "spearman")
		_selectedUnitType = EUT_SPEARMAN;
}

} // namespace qrw
