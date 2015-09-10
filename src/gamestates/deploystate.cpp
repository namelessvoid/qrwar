#include "gamestates/deploystate.hpp"

namespace qrw
{

DeployState::DeployState(sf::RenderWindow* renderWindow)
	: GameState(renderWindow, EGameStateId::EGSID_DEPLOY_STATE)
{

}

DeployState::~DeployState()
{

}

void DeployState::draw()
{

}

EGameStateId DeployState::update()
{
	return EGameStateId::EGSID_NO_CHANGE;
}

} // namespace qrw
