#ifndef QRW_INTRO_HPP
#define QRW_INTRO_HPP

#include "gamestates/gamestate.hpp"

// Foreward declarations
namespace sf
{
class RenderWindow;
class Event;
class Texture;
class Sprite;
}

namespace qrw
{

class IntroState : public GameState
{
public:
	IntroState(sf::RenderWindow* renderWindow);

	~IntroState();

	void init(GameState* previousState);

	EGameStateId update();

	void draw();

	void handleEvent(sf::Event &event);

	EGameStateId getId();

private:
	bool _advanceToNextState;

	sf::Texture* _splashTexture;
	sf::Sprite* _splashSprite;
};

} // namespace qrw

#endif // QRW_INTRO_HPP
