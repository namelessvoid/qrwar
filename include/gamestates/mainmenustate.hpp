#ifndef QRW_MAINMENUSTATE_H
#define QRW_MAINMENUSTATE_H

#include "gamestates/gamestate.hpp"

// Foreward declarations
namespace sf
{
class RenderWindow;
class Event;
}

namespace qrw
{

class MainMenuState : public GameState
{
public:
	MainMenuState(sf::RenderWindow* renderWindow);

	void init(GameState *previousState);

	EGameStateId update();

	void draw();

	void handleEvent(sf::Event &event);
};

} // namespace qrw

#endif // QRW_MAINMENUSTATE_H
