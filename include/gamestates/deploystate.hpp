#ifndef QRW_DEPLOYSTATE_HPP
#define QRW_DEPLOYSTATE_HPP

#include "gamestates/gamestate.hpp"

namespace qrw
{

class DeployState : public GameState
{
public:
	DeployState(sf::RenderWindow* renderWindow);

	virtual ~DeployState();

	virtual void draw();

	virtual qrw::EGameStateId update();
};

} // namespace qrw

#endif // QRW_DEPLOYSTATE_HPP
