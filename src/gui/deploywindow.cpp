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
	  buttongroup(new ButtonGroup()),
	  startbutton(new Button(guihandler->getRenderWindow())),
	  defaultfont(new sf::Font()),
	  title(new sf::Text())
	{
		defaultfont->loadFromFile("./res/font/Knigqst.ttf");
		title->setFont(*defaultfont);
		title->setString("Deployment");
		title->setPosition(630, 0);

		TextureManager* texturemgr = TextureManager::getInstance();
		for(int i = 0; i < BUTTONCOUNT; ++i)
		{
			radiobuttons[i] = new RadioToggleButton(
				guihandler->getRenderWindow(), buttongroup);
			radiobuttons[i]->setScale(1, 1);

			// Set positions
			float x = 625 + (i % 3) * 35;
			float y = 30 + (i / 3) * 35;
			radiobuttons[i]->setPosition(x, y);
		}
		radiobuttons[0]->setTextures(texturemgr->getTexture("p1swordman"),
			texturemgr->getTexture("p1swordman"),
			texturemgr->getTexture("p1swordman"));
		radiobuttons[1]->setTextures(texturemgr->getTexture("p1archer"),
			texturemgr->getTexture("p1archer"),
			texturemgr->getTexture("p1archer"));
		radiobuttons[2]->setTextures(texturemgr->getTexture("p1spearman"),
			texturemgr->getTexture("p1spearman"),
			texturemgr->getTexture("p1spearman"));
		radiobuttons[3]->setTextures(texturemgr->getTexture("p2swordman"),
			texturemgr->getTexture("p2swordman"),
			texturemgr->getTexture("p2swordman"));
		radiobuttons[4]->setTextures(texturemgr->getTexture("p2archer"),
			texturemgr->getTexture("p2archer"),
			texturemgr->getTexture("p2archer"));
		radiobuttons[5]->setTextures(texturemgr->getTexture("p2spearman"),
			texturemgr->getTexture("p2spearman"),
			texturemgr->getTexture("p2spearman"));
		radiobuttons[6]->setTextures(texturemgr->getTexture("wood"),
			texturemgr->getTexture("wood"),
			texturemgr->getTexture("wood"));
		radiobuttons[7]->setTextures(texturemgr->getTexture("hill"),
			texturemgr->getTexture("hill"),
			texturemgr->getTexture("hill"));
		radiobuttons[8]->setTextures(texturemgr->getTexture("wall"),
			texturemgr->getTexture("wall"),
			texturemgr->getTexture("wall"));

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
		for(int i = 0; i < BUTTONCOUNT; ++i)
			radiobuttons[i]->updateSprite();
		startbutton->updateSprite();
	}
	
	void DeployWindow::draw(sf::RenderTarget& target,
		sf::RenderStates states) const
	{
		if(visible == false)
			return;

		for(int i = 0; i < BUTTONCOUNT; ++i)
			radiobuttons[i]->renderTo(target);

		target.draw(*title);
		target.draw(*startbutton);
	}

	void DeployWindow::update()
	{
	}

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
		for(int i = 0; i < BUTTONCOUNT; ++i)
			radiobuttons[i]->handleEvent(event);
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
		}
	}
}