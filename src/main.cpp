#include "qrwar.hpp"

//#include <SFML/Graphics/Sprite.hpp>

//#include "engine/board.hpp"
//#include "engine/square.hpp"
//#include "engine/terrain.hpp"
//#include "engine/unit.hpp"
//#include "engine/engine.hpp"

//#include "gui/guihandler.hpp"
//#include "gui/imagemanager.hpp"
//#include "gui/texturemanager.hpp"

//#include "config/tilesetprocessor.hpp"
//#include "config/settings.hpp"

int main(int argc, char const *argv[])
{
//	// Create engine
//	qrw::Engine engine;
//	engine.init(10, 4);

//	// Setup random board for test dings
//	qrw::Board* board = engine.getBoard();
//	qrw::Terrain* terrain1 = new qrw::Terrain(qrw::ET_WOOD, 1, 2);
//	board->getSquare(0, 0)->setTerrain(terrain1);
//	qrw::Terrain* terrain2 = new qrw::Terrain(qrw::ET_HILL, 3, -1);
//	board->getSquare(1, 2)->setTerrain(terrain2);
//	qrw::Terrain* terrain3 = new qrw::Terrain(qrw::ET_WALL, 2, 2);
//	board->getSquare(5, 1)->setTerrain(terrain3);

//	// Create the gui
//	qrw::GuiHandler guihandler(&engine, &renderwindow);

//	// Create clock for time measurement
//	sf::Clock clock;
//	float elapsedtime;

//	sf::Event event;

//	// Render loop for splash screen
//	bool quitsplash = false;
//	while(!quitsplash)
//	{
//		while(renderwindow.pollEvent(event))
//		{
//			if(event.type == sf::Event::MouseButtonReleased || event.type == sf::Event::KeyPressed)
//				quitsplash = true;
//		}
//		renderwindow.display();
//	}
//	delete splashsprite;
//	delete splashtexture;

//	// Initialize "real" window
//	renderwindow.create(
//		sf::VideoMode(settings->getResolutionX(), settings->getResolutionY()),
//		"Quad-Ruled War",
//		style
//	);

//	sf::View camera(sf::FloatRect(0.0f, 0.0f, settings->getResolutionX(), settings->getResolutionY()));
//	renderwindow.setView(camera);

//	// Start main game loop
//	while(!guihandler.getQuit())
//	{
//		elapsedtime = clock.restart().asSeconds();
//		// Event handling
//		while(renderwindow.pollEvent(event))
//		{
//			if(event.type == sf::Event::Resized)
//			{
//				std::cout << "new width: " << event.size.width << std::endl;
//				std::cout << "new height: " << event.size.height << std::endl;
//				camera.reset(sf::FloatRect(0.0f, 0.0f, event.size.width, event.size.height));
//				camera.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
//				renderwindow.setView(camera);
//			}
//			if(event.type == sf::Event::KeyPressed)
//			{
//				if(event.key.code == sf::Keyboard::W)
//				{
//					camera.move(0.0, -1.0);
//					renderwindow.setView(camera);
//				}
//			}

//			guihandler.HandleEvent(event);
//		} // while(poll-event)

//		// Rendering
//		renderwindow.clear(sf::Color::Black);

//		guihandler.Update(elapsedtime);
//		guihandler.display(renderwindow);

//		renderwindow.display();
//	}

	qrw::QRWar qrwar;

	qrwar.run();

	return 0;
}
