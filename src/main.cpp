#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "gui/guihandler.hpp"
#include "gui/cursor.hpp"
#include "engine/engine.hpp"

#include "gui/boardrenderer.hpp"

#include "engine/terrain.hpp"
#include "engine/unit.hpp"


int main(int argc, char const *argv[])
{
	sf::Vector2f windowsize(800, 600);
	qrw::Engine engine;
	engine.init(10, 4);
	qrw::GuiHandler guihandler(&engine, windowsize);

	
// Setup random board for test dings
qrw::Board* board = engine.getBoard();
qrw::Terrain terrain1(qrw::ET_WOOD, 0, 0);
board->getSquare(0, 0)->setTerrain(&terrain1);
qrw::Terrain terrain2(qrw::ET_HILL, 0, 0);
board->getSquare(1, 2)->setTerrain(&terrain2);

	sf::RenderWindow renderwindow(sf::VideoMode(windowsize.x, windowsize.y), "Quad-Ruled War", sf::Style::Default);
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