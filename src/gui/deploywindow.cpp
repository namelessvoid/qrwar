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
	: _engine(engine),
	  _ingamewindow(ingamewindow),
	  _buttongroup(new namelessgui::ButtonGroup()),
	  // TODO dynamic size
	  _startbutton(new namelessgui::Button(guihandler->getRenderWindow(), 150.0, 40.0)),
	  _defaultfont(new sf::Font()),
	  _title(new namelessgui::Label(guihandler->getRenderWindow()))
	{
		setPosition(620, 0);
		setSize(sf::Vector2f(200, 600));

		_defaultfont->loadFromFile("./res/font/Knigqst.ttf");
		_title->setFont(*_defaultfont);
		_title->setText("Deployment");
		// TODO dynamic positioning
		_title->setPosition(630, 0);
		addWidget(_title);

		TextureManager* texturemgr = TextureManager::getInstance();
		for(int i = 0; i < BUTTONCOUNT; ++i)
		{
			// TODO dynamic size
			_radiobuttons[i] = new namelessgui::RadioToggleButton(guihandler->getRenderWindow(), _buttongroup, 120.0, 50.0);
			_radiobuttons[i]->setScale(1.5, 1.5);

			// Set positions
			// TODO dynamic positioning
			float x = 650;
			float y = 35 + i * 50;
			_radiobuttons[i]->setPosition(x, y);

			addWidget(_radiobuttons[i]);
		}
		_radiobuttons[0]->setTextures(texturemgr->getTexture("p1swordman"),
			texturemgr->getTexture("p1swordman"),
			texturemgr->getTexture("p1swordman"));
		_radiobuttons[1]->setTextures(texturemgr->getTexture("p1archer"),
			texturemgr->getTexture("p1archer"),
			texturemgr->getTexture("p1archer"));
		_radiobuttons[2]->setTextures(texturemgr->getTexture("p1spearman"),
			texturemgr->getTexture("p1spearman"),
			texturemgr->getTexture("p1spearman"));
		_radiobuttons[3]->setTextures(texturemgr->getTexture("p2swordman"),
			texturemgr->getTexture("p2swordman"),
			texturemgr->getTexture("p2swordman"));
		_radiobuttons[4]->setTextures(texturemgr->getTexture("p2archer"),
			texturemgr->getTexture("p2archer"),
			texturemgr->getTexture("p2archer"));
		_radiobuttons[5]->setTextures(texturemgr->getTexture("p2spearman"),
			texturemgr->getTexture("p2spearman"),
			texturemgr->getTexture("p2spearman"));
		_radiobuttons[6]->setTextures(texturemgr->getTexture("wood"),
			texturemgr->getTexture("wood"),
			texturemgr->getTexture("wood"));
		_radiobuttons[6]->setText("Wood");
		_radiobuttons[7]->setTextures(texturemgr->getTexture("hill"),
			texturemgr->getTexture("hill"),
			texturemgr->getTexture("hill"));
		_radiobuttons[7]->setText("Hill");
		_radiobuttons[8]->setTextures(texturemgr->getTexture("wall"),
			texturemgr->getTexture("wall"),
			texturemgr->getTexture("wall"));
		_radiobuttons[8]->setText("Tower");
		_radiobuttons[9]->setTextures(texturemgr->getTexture("plainsquare"),
			texturemgr->getTexture("plainsquare"),
			texturemgr->getTexture("plainsquare"));
		_radiobuttons[9]->setText("No Terrain");

		_startbutton->setTextures(texturemgr->getTexture("startbutton"),
			texturemgr->getTexture("startbutton"),
			texturemgr->getTexture("startbutton"));
		_startbutton->setPosition(sf::Vector2f(650, 560));
		_startbutton->signalclicked.connect(
			std::bind(&DeployWindow::startbuttonClicked, this));
		addWidget(_startbutton);
	}

	DeployWindow::~DeployWindow()
	{
		delete _startbutton;
		delete _defaultfont;
		delete _title;
	}

	void DeployWindow::update()
	{
		// Set player info text
		std::string text;
		Player* player = NULL;

		for(int i = 0; i < 2; ++i)
		{
			player = _engine->getPlayer(i);

			for(int j = 0; j < EUT_NUMBEROFUNITTYPES; ++j)
			{
				text = "(" + intToString(player->getArmy().getDeployedUnitCount((UNITTYPES)j))
					+ " / " + intToString(player->getArmy().getUnitCount((UNITTYPES)j)) + ")";
				_radiobuttons[j + i * EUT_NUMBEROFUNITTYPES]->setText(text);
			}
		}
	}

	void DeployWindow::startbuttonClicked()
	{
		if(_engine->getStatus() == EES_PREPARE)
		{
			_engine->startGame();
			_ingamewindow->setVisible(true);
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
			if(_radiobuttons[activebuttonid]->getState() == namelessgui::Button::ES_ACTIVE)
				break;
		}

		// Get cursor position
		Cursor* cursor = Cursor::getCursor();

		// Remove terrain
		if(activebuttonid == 9)
		{
			_engine->removeTerrain(cursor->getPosition());
		}
		// Place unit
		else if(activebuttonid >= 0 && activebuttonid < 2 * EUT_NUMBEROFUNITTYPES)
		{
			int playerid = activebuttonid / EUT_NUMBEROFUNITTYPES;
			UNITTYPES unittype = (UNITTYPES)(activebuttonid % EUT_NUMBEROFUNITTYPES);

			_engine->placeUnit(cursor->getPosition(), playerid, unittype);
			update();
		}
		// Place terrain
		else
		{
			TERRAINTYPES terraintype = (TERRAINTYPES)(activebuttonid
				- (2 * EUT_NUMBEROFUNITTYPES));
			_engine->placeTerrain(cursor->getPosition(), terraintype);
		}
	}

	void DeployWindow::moveUnit()
	{
		Cursor* cursor = Cursor::getCursor();
		Cursor* child = cursor->getChild();

		if(child == NULL)
			return;

		_engine->moveUnitDeployment(cursor->getPosition(), child->getPosition());

		cursor->setPosition(child->getPosition());

		cursor->despawnChild();
		printf("move unit\n");
	}
}
