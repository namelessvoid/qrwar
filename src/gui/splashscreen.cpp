#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include "gui/splashscreen.hpp"

namespace qrw
{
	SplashScreen::SplashScreen(std::string imgpath)
	: closeable(false)
	{
		spritetex = new sf::Texture();
		spritetex->loadFromFile(imgpath);
		sprite = new sf::Sprite(*spritetex);
		renderwindow = new sf::RenderWindow(sf::VideoMode(640, 480), "QRW Loading...", sf::Style::Default);
		renderwindow->setView(sf::View(sf::FloatRect(0, 0, 640, 480)));
	}
	SplashScreen::~SplashScreen()
	{
		delete sprite;
		sprite = NULL;
		delete spritetex;
		spritetex = NULL;
		delete renderwindow;
		renderwindow = NULL;
	}

	void SplashScreen::setCloseable(bool closeable)
	{
		this->closeable = closeable;
	}

	bool SplashScreen::show()
	{
		sf::Event event;
		bool quit = false;
		while(quit == false)
		{
			while(renderwindow->pollEvent(event))
			{
				if(event.type == sf::Event::KeyPressed
					&& closeable == true)
				{
				 	quit = true;
				 }
			}
			renderwindow->clear();
			sprite->setPosition(sf::Vector2f(0, 0));
			sprite->setScale(sf::Vector2f(1, 1));
			renderwindow->draw(*sprite);
			renderwindow->display();
		}
		return true;
	}
}