#include "gamestates/introstate.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "config/settings.hpp"
#include "config/tilesetprocessor.hpp"
#include "gui/imagemanager.hpp"
#include "gui/texturemanager.hpp"


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
		sf::VideoMode(640, 240),
		"Quad-Ruled War - Loading...",
		sf::Style::None
	);

	_advanceToNextState = false;

	_splashTexture = new sf::Texture();
	_splashTexture->loadFromFile("./res/img/splash.png");
	_splashSprite = new sf::Sprite();
	_splashSprite->setTexture(*_splashTexture);
}

EGameStateId IntroState::update()
{
	if(_advanceToNextState)
	{
		delete _splashTexture;
		delete _splashSprite;

		return EGameStateId::EGSID_MAIN_MENU_STATE;
	}

	return EGameStateId::EGSID_NO_CHANGE;
}

void IntroState::draw()
{
	_renderWindow->draw(*_splashSprite);
	_renderWindow->display();
}

void IntroState::handleEvent(sf::Event& event)
{
	if(event.type == sf::Event::KeyPressed)
		_advanceToNextState = true;
}

} // namespace qrw
