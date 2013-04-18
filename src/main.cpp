#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "gui/guihandler.hpp"
#include "graphics/cursor.hpp"
#include "engine/engine.hpp"

#include "graphics/boardrenderer.hpp"
#include "engine/terrain.hpp"


void moveUnit(qrw::Cursor* cursor, qrw::Engine* engine)
{
	int orx = cursor->getPosition().x;
	int ory = cursor->getPosition().y;
	int destx = cursor->getChild()->getPosition().x;
	int desty = cursor->getChild()->getPosition().y;
	if(engine->moveUnit(orx, ory, destx, desty) == 0)
		cursor->despawnChild();
}


int main(int argc, char const *argv[])
{
	qrw::GuiHandler guihandler;

	qrw::Engine engine;
// Setup random board for test dings
qrw::Board board(25, 18);
qrw::Terrain terrain1(qrw::ET_WOOD, 0, 0);
board.getSquare(0, 0)->setTerrain(&terrain1);
qrw::Terrain terrain2(qrw::ET_HILL, 0, 0);
board.getSquare(1, 2)->setTerrain(&terrain2);

qrw::BoardRenderer boardrenderer;
boardrenderer.setBoard(&board);

qrw::Cursor::getCursor()->setBoard(&board);

	sf::RenderWindow renderwindow(sf::VideoMode(800, 600), "Quad-Ruled War", sf::Style::Default);
	sf::View camera(sf::FloatRect(0.0f, 0.0f, 800.0f, 600.0f));
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
		{
			// Toggle gui
			if(event.type == sf::Event::KeyPressed)
				if(event.key.code == sf::Keyboard::F1)
					guihandler.toggleGui();
			// Let the gui handle the event
			if(guihandler.guiVisible())
				guihandler.HandleEvent(event);
			else
			{
				if(event.type == sf::Event::KeyPressed)
				{
					qrw::Cursor* cursor = qrw::Cursor::getCursor();
					if(event.key.code == sf::Keyboard::Up)
						cursor->move(0, -1);
					else if(event.key.code == sf::Keyboard::Down)
						cursor->move(0, 1);
					else if(event.key.code == sf::Keyboard::Right)
						cursor->move(1, 0);
					else if(event.key.code == sf::Keyboard::Left)
						cursor->move(-1, 0);
					else if(event.key.code == sf::Keyboard::Return)
						cursor->spawnChild();
					else if(event.key.code == sf::Keyboard::Escape)
						cursor->despawnChild();
					else if(event.key.code == sf::Keyboard::Return)
						if(cursor->getChild() != 0)
							moveUnit(cursor, &engine);
				}
			}
		}

		// Rendering
		renderwindow.clear(sf::Color::Black);
		renderwindow.draw(rect);
renderwindow.draw(boardrenderer);
		guihandler.Update(elapsedtime);
		guihandler.display(renderwindow);
		renderwindow.display();
	}

	return 0;
}