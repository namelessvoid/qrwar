#ifndef QRW_QRWAR_HPP
#define QRW_QRWAR_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include <map>

#include "gamestates/gamestate.hpp"

namespace qrw
{

class QRWar
{
public:
	QRWar();

	void run();

private:
	sf::RenderWindow _renderWindow;

	std::map<EGameStateId, GameState*> _gameStates;
};

} // namespace qrw

#endif // QRW_QRWAR_HPP
