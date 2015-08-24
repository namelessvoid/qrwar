#ifndef QRW_INTRO_HPP
#define QRW_INTRO_HPP

#include "gamestates/gamestate.hpp"

// Foreward declarations
namespace sf
{
class RenderWindow;
}

namespace qrw
{

class IntroState : public GameState
{
public:
	IntroState(sf::RenderWindow* renderWindow);

	~IntroState();

	EGameStateId update();

	void draw();

	EGameStateId getId();
};

} // namespace qrw

#endif // QRW_INTRO_HPP
