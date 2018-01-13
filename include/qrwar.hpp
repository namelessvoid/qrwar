#ifndef QRW_QRWAR_HPP
#define QRW_QRWAR_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "gamestates/gamestate.hpp"

#include "rendering/guicamera.hpp"

namespace qrw
{

class QRWar
{
public:
	QRWar();

	~QRWar();

	void run();

private:
	void preloadResources();

	GameState* createGameState(EGameStateId id);

	sf::RenderWindow _renderWindow;

	GameState* _currentState;

	GuiCamera guiCamera_;
};

} // namespace qrw

#endif // QRW_QRWAR_HPP
