#include "gamestates/intro.hpp"

#include <SFML/Window/Event.hpp>

#include <iostream>

namespace qrw
{

IntroState::IntroState(sf::RenderWindow* renderWindow)
	: GameState(renderWindow, EGameStateId::EGSID_INTRO)
{
	_quit = false;
}

IntroState::~IntroState()
{
}

EGameStateId IntroState::update()
{
	if(_quit)
		return EGameStateId::EGSID_QUIT;

	return EGameStateId::EGSID_NO_CHANGE;
}

void IntroState::draw()
{

}

void IntroState::handleEvent(sf::Event& event)
{
	std::cout << "Handle event\n";

	if(event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == sf::Keyboard::Q)
		{
			_quit = true;
		}
	}
}

} // namespace qrw
