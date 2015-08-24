#include "gamestates/intro.hpp"

namespace qrw
{

IntroState::IntroState(sf::RenderWindow* renderWindow)
	: GameState(renderWindow, EGameStateId::EGSID_INTRO)
{

}

IntroState::~IntroState()
{
}

EGameStateId IntroState::update()
{
	return EGameStateId::EGSID_NO_CHANGE;
}

void IntroState::draw()
{

}

} // namespace qrw
