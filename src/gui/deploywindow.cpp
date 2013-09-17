#include <stdio.h>

#include "tostring.hpp"
#include "gui/deploywindow.hpp"
#include "gui/texturemanager.hpp"
#include "gui/guihandler.hpp"
#include "gui/cursor.hpp"

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
			radiobuttons[i]->setScale(1.5, 1.5);

			// Set positions
			float x = 650;
			float y = 35 + i * 50;
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
		radiobuttons[6]->setText("Wood");
		radiobuttons[7]->setTextures(texturemgr->getTexture("hill"),
			texturemgr->getTexture("hill"),
			texturemgr->getTexture("hill"));
		radiobuttons[7]->setText("Hill");
		radiobuttons[8]->setTextures(texturemgr->getTexture("wall"),
			texturemgr->getTexture("wall"),
			texturemgr->getTexture("wall"));
		radiobuttons[8]->setText("Tower");

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
		// Set player info text
		std::string text;
		for(int i = 0; i < 2 * EUT_NUMBEROFUNITTYPES; ++i)
		{
			text = "(" + intToString(
				engine->getPlayer(i / EUT_NUMBEROFUNITTYPES)
				->getNumberOfUnits()[i % EUT_NUMBEROFUNITTYPES])
			+ " / " + intToString(playerunits[i]) + ")";
			radiobuttons[i]->setText(text);
		}
	}

	void DeployWindow::setPlayerUnits(int playerunits[])
	{
		for(int i = 0; i < 2 * EUT_NUMBEROFUNITTYPES; ++i)
		{
			this->playerunits[i] = playerunits[i];
		}
	}

	void DeployWindow::handleEvent(const sf::Event& event)
	{
		if(visible == false)
			return;

		if(event.type == sf::Event::KeyPressed)
		{
			if(event.key.code == sf::Keyboard::Return)
			{
				placeEntity();
			}
			return;
		}
		for(int i = 0; i < BUTTONCOUNT; ++i)
			radiobuttons[i]->handleEvent(event);
		startbutton->handleEvent(event);
	}

	void DeployWindow::startbuttonClicked()
	{
		if(engine->getStatus() == EES_PREPARE)
		{
			engine->startGame();
			ingamewindow->setVisible(true);
			setVisible(false);
		}
	}

	void DeployWindow::placeEntity()
	{
		printf("place entity\n");
		// get active button
		int activebuttonid = 0;
		for(activebuttonid = 0;
			activebuttonid < BUTTONCOUNT;
			 ++activebuttonid)
		{
			if(radiobuttons[activebuttonid]->getState() == Button::ES_ACTIVE)
				break;
		}

		// Get cursor position
		Cursor* cursor = Cursor::getCursor();
		int x = cursor->getPosition().x;
		int y = cursor->getPosition().y;

		// Place unit
		if(activebuttonid >= 0 && activebuttonid < 2 * EUT_NUMBEROFUNITTYPES)
		{
			int playerid = activebuttonid / EUT_NUMBEROFUNITTYPES;
			Player* player = engine->getPlayer(playerid);
			UNITTYPES unittype = (UNITTYPES)(activebuttonid % EUT_NUMBEROFUNITTYPES);

			// Check if all units have been placed
			if(player->getNumberOfUnits()[unittype] >= playerunits[activebuttonid])
				return;

			engine->placeUnit(x, y, playerid, unittype);
			update();
		}
		// Place terrain
		else
		{
			TERRAINTYPES terraintype = (TERRAINTYPES)(activebuttonid 
				- (2 * EUT_NUMBEROFUNITTYPES));
			engine->placeTerrain(x, y, terraintype);
		}
	}
}