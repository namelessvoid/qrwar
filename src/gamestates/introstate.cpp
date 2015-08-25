#include "gamestates/introstate.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

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

	// Start initialization of qrw...
	// Load Settings
	qrw::Settings* settings = qrw::Settings::getInstance();
	settings->loadFromFile();

	// Preload image resources
	qrw::ImageManager* imgmgr = qrw::ImageManager::getInstance();
	imgmgr->loadImage("p1swordman", "./res/img/units/p1swordman.png");
	imgmgr->loadImage("p1archer", "./res/img/units/p1archer.png");
	imgmgr->loadImage("p1spearman", "./res/img/units/p1spearman.png");
	imgmgr->loadImage("p2swordman", "./res/img/units/p2swordman.png");
	imgmgr->loadImage("p2archer", "./res/img/units/p2archer.png");
	imgmgr->loadImage("p2spearman", "./res/img/units/p2spearman.png");
	imgmgr->loadImage("plainsquare", "./res/img/plainsquare.png");

	TextureManager::getInstance()->loadTexture("mainmenubackground", "./res/img/mainmenubackground.png");

	// Loading tilesets
	qrw::TilesetProcessor tilesetprocessor;
	tilesetprocessor.loadTileset(settings->getEntityTilesetPath());
	tilesetprocessor.loadTileset(settings->getGuiTilesetPath());
}

void IntroState::handleEvent(sf::Event& event)
{
	std::cout << "Handle event\n";

	if(event.type == sf::Event::KeyPressed)
		_advanceToNextState = true;
}

} // namespace qrw
