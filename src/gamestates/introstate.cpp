#include "gamestates/introstate.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

namespace qrw
{

IntroState::IntroState(sf::RenderWindow* renderWindow)
	: GameState(renderWindow, EGameStateId::EGSID_INTRO_STATE)
{
}

IntroState::~IntroState()
{
}

void IntroState::init(GameState* previousState)
{
	// Create render window
	_renderWindow->create(
		sf::VideoMode(640, 480),
		"Quad-Ruled War - Loading...",
		sf::Style::None
	);

	_quit = false;

	_splashTexture = new sf::Texture();
	_splashTexture->loadFromFile("./res/img/splash.png");
	_splashSprite = new sf::Sprite();
	_splashSprite->setTexture(*_splashTexture);
}

EGameStateId IntroState::update()
{
	if(_quit)
	{
		delete _splashTexture;
		delete _splashSprite;

		return EGameStateId::EGSID_QUIT;
	}

	return EGameStateId::EGSID_NO_CHANGE;
}

void IntroState::draw()
{
	_renderWindow->draw(*_splashSprite);
}

void IntroState::handleEvent(sf::Event& event)
{
	std::cout << "Handle event\n";

	if(event.type == sf::Event::KeyPressed)
	{
		_quit = true;
	}
}

} // namespace qrw
