#ifndef QRW_MAINMENUSTATE_H
#define QRW_MAINMENUSTATE_H

#include "gamestates/gamestate.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

// Foreward declarations
namespace sf
{
class RenderWindow;
class Event;
class RectangleShape;
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

private:
	sf::RectangleShape _background;
};

} // namespace qrw

#endif // QRW_MAINMENUSTATE_H
