#include <stdio.h>

#include <thread>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "gui/guihandler.hpp"
#include "gui/cursor.hpp"
#include "engine/engine.hpp"

#include "gui/boardrenderer.hpp"

#include "engine/terrain.hpp"
#include "engine/unit.hpp"

#include "gui/splashscreen.hpp"
#include "gui/imagemanager.hpp"
#include "gui/texturemanager.hpp"


int main(int argc, char const *argv[])
{
	// Create and show splash
	qrw::SplashScreen* splash = new qrw::SplashScreen("./res/img/splash.png");
	std::thread splashthread(&qrw::SplashScreen::show, splash);

	// Preload image resources.
	qrw::ImageManager* imgmgr = qrw::ImageManager::getInstance();
	imgmgr->loadImage("p1swordman", "./res/img/units/p1swordman.png");
	imgmgr->loadImage("p1archer", "./res/img/units/p1archer.png");
	imgmgr->loadImage("p1spearman", "./res/img/units/p1spearman.png");
	imgmgr->loadImage("p2swordman", "./res/img/units/p2swordman.png");
	imgmgr->loadImage("p2archer", "./res/img/units/p2archer.png");
	imgmgr->loadImage("p2spearman", "./res/img/units/p2spearman.png");
	imgmgr->loadImage("plainsquare", "./res/img/plainsquare.png");
	// Preload texture resources.
	qrw::TextureManager* texturemanager = qrw::TextureManager::getInstance();
	texturemanager->loadTexture("plainsquare", "./res/img/plainsquare.png");
	texturemanager->loadTexture("p1swordman", "./res/img/units/p1swordman.png");
	texturemanager->loadTexture("p1archer", "./res/img/units/p1archer.png");
	texturemanager->loadTexture("p1spearman", "./res/img/units/p1spearman.png");
	texturemanager->loadTexture("p2swordman", "./res/img/units/p2swordman.png");
	texturemanager->loadTexture("p2archer", "./res/img/units/p2archer.png");
	texturemanager->loadTexture("p2spearman", "./res/img/units/p2spearman.png");
	texturemanager->loadTexture("wood", "./res/img/terrain/wood.png");
	texturemanager->loadTexture("hill", "./res/img/terrain/hill.png");
	texturemanager->loadTexture("nextbutton", "./res/img/gui/nextbutton.png");
	texturemanager->loadTexture("nextbutton_hover", "./res/img/gui/nextbutton_hover.png");
	texturemanager->loadTexture("nextbutton_active", "./res/img/gui/nextbutton_active.png");
	texturemanager->loadTexture("health", "./res/img/gui/health.png");
	texturemanager->loadTexture("attack", "./res/img/gui/attack.png");
	texturemanager->loadTexture("defense", "./res/img/gui/defense.png");

	splash->setCloseable(true);
	splashthread.join();
	delete splash;

	sf::Vector2f windowsize(800, 600);
	qrw::Engine engine;
	engine.init(10, 4);

	
// Setup random board for test dings
qrw::Board* board = engine.getBoard();
qrw::Terrain terrain1(qrw::ET_WOOD, 1, 2);
board->getSquare(0, 0)->setTerrain(&terrain1);
qrw::Terrain terrain2(qrw::ET_HILL, 3, -1);
board->getSquare(1, 2)->setTerrain(&terrain2);

	sf::RenderWindow renderwindow(sf::VideoMode(windowsize.x, windowsize.y), "Quad-Ruled War", sf::Style::Default);
	qrw::GuiHandler guihandler(&engine, &renderwindow);
	sf::View camera(sf::FloatRect(0.0f, 0.0f, windowsize.x, windowsize.y));
	renderwindow.setView(camera);

	sf::RectangleShape rect(sf::Vector2f(10.0f, 10.0f));
	rect.setFillColor(sf::Color::Green);

	sf::Clock clock;
	float elapsedtime;

	while(!guihandler.getQuit())
	{
		elapsedtime = clock.restart().asSeconds();
		// Event handling
		sf::Event event;
		while(renderwindow.pollEvent(event))
			guihandler.HandleEvent(event);

		// Rendering
		renderwindow.clear(sf::Color::Black);
		renderwindow.draw(rect);

		guihandler.Update(elapsedtime);
		guihandler.display(renderwindow);
		
		renderwindow.display();
	}

	return 0;
}