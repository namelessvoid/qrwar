#include <stdio.h>

#include "gui/deploywindow.hpp"

#include "engine/engine.hpp"
#include "engine/player.hpp"

#include "tostring.hpp"
#include "gui/texturemanager.hpp"
#include "gui/guihandler.hpp"
#include "gui/ingamewindow.hpp"
#include "gui/cursor.hpp"

#include "gui/ng/radiotogglebutton.hpp"
#include "gui/ng/buttongroup.hpp"

namespace qrw
{
	DeployWindow::DeployWindow(Engine* engine, GuiHandler* guihandler, IngameWindow* ingamewindow)
	: engine(engine),
	  ingamewindow(ingamewindow),
	  buttongroup(new namelessgui::ButtonGroup()),
	  // TODO dynamic size
	  startbutton(new namelessgui::Button(guihandler->getRenderWindow(), 150.0, 40.0)),
	  defaultfont(new sf::Font()),
	  title(new namelessgui::Label(guihandler->getRenderWindow()))
	{
		setPosition(620, 0);
		setSize(sf::Vector2f(200, 600));

		defaultfont->loadFromFile("./res/font/Knigqst.ttf");
		title->setFont(*defaultfont);
		title->setText("Deployment");
		// TODO dynamic positioning
		title->setPosition(630, 0);
		addWidget(title);

		TextureManager* texturemgr = TextureManager::getInstance();
		for(int i = 0; i < BUTTONCOUNT; ++i)
		{
			// TODO dynamic size
			radiobuttons[i] = new namelessgui::RadioToggleButton(guihandler->getRenderWindow(), buttongroup, 120.0, 50.0);
			radiobuttons[i]->setScale(1.5, 1.5);

			// Set positions
			// TODO dynamic positioning
			float x = 650;
			float y = 35 + i * 50;
			radiobuttons[i]->setPosition(x, y);

			addWidget(radiobuttons[i]);
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
		radiobuttons[9]->setTextures(texturemgr->getTexture("plainsquare"),
			texturemgr->getTexture("plainsquare"),
			texturemgr->getTexture("plainsquare"));
		radiobuttons[9]->setText("No Terrain");

		startbutton->setTextures(texturemgr->getTexture("startbutton"),
			texturemgr->getTexture("startbutton"),
			texturemgr->getTexture("startbutton"));
		startbutton->setPosition(sf::Vector2f(650, 560));
		startbutton->signalclicked.connect(
			std::bind(&DeployWindow::startbuttonClicked, this));
		addWidget(startbutton);
	}

	DeployWindow::~DeployWindow()
	{
		delete startbutton;
		delete defaultfont;
		delete title;
	}

	void DeployWindow::update()
	{
		// Set player info text
		std::string text;
		Player* player = NULL;

		for(int i = 0; i < 2; ++i)
		{
			player = engine->getPlayer(i);

			for(int j = 0; j < EUT_NUMBEROFUNITTYPES; ++j)
			{
				text = "(" + intToString(player->getArmy().getDeployedUnitCount((UNITTYPES)j))
					+ " / " + intToString(player->getArmy().getUnitCount((UNITTYPES)j)) + ")";
				radiobuttons[j + i * EUT_NUMBEROFUNITTYPES]->setText(text);
			}
		}
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
			if(radiobuttons[activebuttonid]->getState() == namelessgui::Button::ES_ACTIVE)
				break;
		}

		// Get cursor position
		Cursor* cursor = Cursor::getCursor();

		// Remove terrain
		if(activebuttonid == 9)
		{
			engine->removeTerrain(cursor->getPosition());
		}
		// Place unit
		else if(activebuttonid >= 0 && activebuttonid < 2 * EUT_NUMBEROFUNITTYPES)
		{
			int playerid = activebuttonid / EUT_NUMBEROFUNITTYPES;
			Player* player = engine->getPlayer(playerid);
			UNITTYPES unittype = (UNITTYPES)(activebuttonid % EUT_NUMBEROFUNITTYPES);

			engine->placeUnit(cursor->getPosition(), playerid, unittype);
			update();
		}
		// Place terrain
		else
		{
			TERRAINTYPES terraintype = (TERRAINTYPES)(activebuttonid
				- (2 * EUT_NUMBEROFUNITTYPES));
			engine->placeTerrain(cursor->getPosition(), terraintype);
		}
	}

	void DeployWindow::moveUnit()
	{
		Cursor* cursor = Cursor::getCursor();
		Cursor* child = cursor->getChild();

		if(child == NULL)
			return;

		engine->moveUnitDeployment(cursor->getPosition(), child->getPosition());

		cursor->setPosition(child->getPosition());

		cursor->despawnChild();
		printf("move unit\n");
	}
}
