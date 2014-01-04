#include <stdio.h>

#include <thread>
#include <SFML/Graphics/RenderWindow.hpp>

#include "engine/terrain.hpp"
#include "engine/unit.hpp"
#include "engine/engine.hpp"

#include "gui/cursor.hpp"
#include "gui/guihandler.hpp"
#include "gui/splashscreen.hpp"
#include "gui/imagemanager.hpp"
#include "gui/texturemanager.hpp"

#include "config/tilesetprocessor.hpp"
#include "config/settings.hpp"


int main(int argc, char const *argv[])
{
	qrw::Settings* settings = qrw::Settings::getInstance();
	settings->loadFromFile();

	// Create and show splash
	//qrw::SplashScreen* splash = new qrw::SplashScreen("./res/img/splash.png");
	//std::thread splashthread(&qrw::SplashScreen::show, splash);

	// Preload image resources.
	qrw::ImageManager* imgmgr = qrw::ImageManager::getInstance();
	imgmgr->loadImage("p1swordman", "./res/img/units/p1swordman.png");
	imgmgr->loadImage("p1archer", "./res/img/units/p1archer.png");
	imgmgr->loadImage("p1spearman", "./res/img/units/p1spearman.png");
	imgmgr->loadImage("p2swordman", "./res/img/units/p2swordman.png");
	imgmgr->loadImage("p2archer", "./res/img/units/p2archer.png");
	imgmgr->loadImage("p2spearman", "./res/img/units/p2spearman.png");
	imgmgr->loadImage("plainsquare", "./res/img/plainsquare.png");

	// Loading tilesets
	qrw::TilesetProcessor tilesetprocessor;
	tilesetprocessor.loadTileset(settings->getEntityTilesetPath());
	tilesetprocessor.loadTileset(settings->getGuiTilesetPath());

	//splash->setCloseable(true);
	//splashthread.join();
	//delete splash;

	qrw::Engine engine;
	engine.init(10, 4);


// Setup random board for test dings
qrw::Board* board = engine.getBoard();
qrw::Terrain* terrain1 = new qrw::Terrain(qrw::ET_WOOD, 1, 2);
board->getSquare(0, 0)->setTerrain(terrain1);
qrw::Terrain* terrain2 = new qrw::Terrain(qrw::ET_HILL, 3, -1);
board->getSquare(1, 2)->setTerrain(terrain2);
qrw::Terrain* terrain3 = new qrw::Terrain(qrw::ET_WALL, 2, 2);
board->getSquare(5, 1)->setTerrain(terrain3);

	// Determine whether fullscreen is enabled
	sf::Uint32 style = sf::Style::Default;
	if(settings->getFullscreen())
		style = sf::Style::Fullscreen;

	sf::RenderWindow renderwindow(
		sf::VideoMode(settings->getResolutionX(), settings->getResolutionY()),
		"Quad-Ruled War",
		style
	);

	qrw::GuiHandler guihandler(&engine, &renderwindow);
	sf::View camera(sf::FloatRect(0.0f, 0.0f, settings->getResolutionX(), settings->getResolutionY()));
	renderwindow.setView(camera);

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

		guihandler.Update(elapsedtime);
		guihandler.display(renderwindow);

		renderwindow.display();
	}

	return 0;
}
