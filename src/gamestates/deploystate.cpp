#include "gamestates/deploystate.hpp"

#include <memory>

#include "gamestates/mapeditorstate.hpp"

namespace qrw
{

DeployState::DeployState(sf::RenderWindow* renderWindow)
	: SceneState(renderWindow, EGameStateId::EGSID_DEPLOY_STATE)
{
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
}

} // namespace qrw
