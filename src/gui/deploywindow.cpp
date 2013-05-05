#include <stdio.h>

#include "gui/deploywindow.hpp"
#include "gui/texturemanager.hpp"
#include "gui/guihandler.hpp"

namespace qrw
{
	DeployWindow::DeployWindow(Engine* engine, GuiHandler* guihandler,
		IngameWindow* ingamewindow)
	: visible(false),
	  engine(engine),
	  ingamewindow(ingamewindow),
	  startbutton(new Button(guihandler->getRenderWindow())),
	  defaultfont(new sf::Font()),
	  title(new sf::Text())
	{
		defaultfont->loadFromFile("./res/font/Knigqst.ttf");
		title->setFont(*defaultfont);
		title->setString("Deployment");
		title->setPosition(630, 0);

		TextureManager* texturemgr = TextureManager::getInstance();
		startbutton->setTextures(texturemgr->getTexture("startbutton"),
			texturemgr->getTexture("startbutton"),
			texturemgr->getTexture("startbutton"));
		startbutton->setPosition(sf::Vector2f(650, 560));
		startbutton->signalclicked.connect(
			std::bind(&DeployWindow::startbuttonClicked, this));
	}

	DeployWindow::~DeployWindow()
	{
		delete startbutton;
		delete defaultfont;
		delete title;
	}

	void DeployWindow::setVisible(bool visible)
	{
		this->visible = visible;
	}
	
	void DeployWindow::draw(sf::RenderTarget& target,
		sf::RenderStates states) const
	{
		if(visible == false)
			return;

		target.draw(*title);
		target.draw(*startbutton);
	}

	void DeployWindow::update()
	{}

	void DeployWindow::setPlayerUnits(int p1units[], int p2units[])
	{
		for(int i = 0; i < EUT_NUMBEROFUNITTYPES; ++i)
		{
			this->p1units[i] = p1units[i];
			this->p2units[i] = p2units[i];
		}
	}

	void DeployWindow::handleEvent(const sf::Event& event)
	{
		startbutton->handleEvent(event);
	}

	void DeployWindow::startbuttonClicked()
	{
		if(engine->getStatus() == EES_PREPARE)
		{
			printf("PlaceUnitWindow: starting game\n");
			engine->startGame();
			ingamewindow->setVisible(true);
			setVisible(false);
			update();
		}
	}
}