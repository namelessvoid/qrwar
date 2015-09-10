#ifndef QRW_DEPLOYSTATE_HPP
#define QRW_DEPLOYSTATE_HPP

#include "gamestates/scenestate.hpp"

#include "engine/board.hpp"

namespace qrw
{

class DeployState : public SceneState
{
public:
	DeployState(sf::RenderWindow* renderWindow);

	virtual ~DeployState();

	virtual qrw::EGameStateId update() override;

	virtual void init(GameState* previousState) override;

private:
	Board::Ptr _board;
};

} // namespace qrw

#endif // QRW_DEPLOYSTATE_HPP
