#include <SFGUI/Button.hpp>
#include <SFGUI/Table.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/Separator.hpp>

#include "tostring.hpp"
#include "engine/engine.hpp"
#include "engine/unit.hpp"
#include "engine/terrain.hpp"
#include "engine/board.hpp"
#include "engine/square.hpp"
#include "gui/ingamewindow.hpp"
#include "gui/cursor.hpp"
#include "gui/imagemanager.hpp"
#include "gui/texturemanager.hpp"
#include "gui/guihandler.hpp"

#include "gui/ng/spritewidget.hpp"
#include "gui/ng/button.hpp"

namespace qrw
{
	IngameWindow::IngameWindow(Engine* engine, GuiHandler* guihandler)
	: engine(engine),
	  guihandler(guihandler),
	  // TODO: Dynamic size
	  endturnbutton(new namelessgui::Button(guihandler->getRenderWindow(), 100.0, 40.0)),
	  playernamelabel(new namelessgui::Label(guihandler->getRenderWindow(), 100.0, 40.0)),

	  unitplainsquare(new namelessgui::SpriteWidget(guihandler->getRenderWindow(), 32, 32)),
	  healthsprite(new namelessgui::SpriteWidget(guihandler->getRenderWindow(), 32, 32)),
	  unitattacksprite(new namelessgui::SpriteWidget(guihandler->getRenderWindow(), 32, 32)),
	  unitdefensesprite(new namelessgui::SpriteWidget(guihandler->getRenderWindow(), 32, 32)),
	  movementsprite(new namelessgui::SpriteWidget(guihandler->getRenderWindow(), 32, 32)),

	  terrainplainsquare(new namelessgui::SpriteWidget(guihandler->getRenderWindow(), 32, 32)),
	  terrainattacksprite(new namelessgui::SpriteWidget(guihandler->getRenderWindow(), 32, 32)),
	  terraindefensesprite(new namelessgui::SpriteWidget(guihandler->getRenderWindow(), 32, 32)),

	  defaultfont(new sf::Font()),

	  healthtext(new namelessgui::Label(guihandler->getRenderWindow())),
	  unitattacktext(new namelessgui::Label(guihandler->getRenderWindow())),
	  unitdefensetext(new namelessgui::Label(guihandler->getRenderWindow())),
	  unitmovementtext(new namelessgui::Label(guihandler->getRenderWindow())),
	  terrainattacktext(new namelessgui::Label(guihandler->getRenderWindow())),
	  terraindefensetext(new namelessgui::Label(guihandler->getRenderWindow()))
	{
		defaultfont->loadFromFile("./res/font/Knigqst.ttf");
		playernamelabel->setFont(*defaultfont);
		playernamelabel->setCharacterSize(25);
		playernamelabel->setText("Player name");
		playernamelabel->setPosition(625.0, 0.0);
		playernamelabel->setColor(sf::Color::White);
		addWidget(playernamelabel);

		TextureManager* texturemanager = TextureManager::getInstance();

		setPosition(620, 0);
		setSize(sf::Vector2f(200, 600));

		// set up sprites for unit information
		sf::Vector2f unitspritepos(630, 40);

		unitplainsquare->setTexture(texturemanager->getTexture("plainsquare"));
		unitplainsquare->setPosition(unitspritepos);
		unitplainsquare->setScale(1.5, 1.5);
		addWidget(unitplainsquare);

		for(int i =  0; i < EUT_NUMBEROFUNITTYPES * 2; ++i)
		{
			unitimages[i] = new namelessgui::SpriteWidget(guihandler->getRenderWindow(), 32, 32);
			unitimages[i]->setPosition(unitspritepos.x, unitspritepos.y);
			unitimages[i]->setScale(1.5, 1.5);
			this->addWidget(unitimages[i]);
			unitimages[i]->setVisible(true);
		}
		unitimages[EUT_SWORDMAN]->setTexture(texturemanager->getTexture("p1swordman"));
		unitimages[EUT_SPEARMAN]->setTexture(texturemanager->getTexture("p1spearman"));
		unitimages[EUT_ARCHER]->setTexture(texturemanager->getTexture("p1archer"));
		std::cout << EUT_NUMBEROFUNITTYPES * 2 - 1 << std::endl;
		unitimages[EUT_NUMBEROFUNITTYPES + EUT_SWORDMAN]->setTexture(texturemanager->getTexture("p2swordman"));
		unitimages[EUT_NUMBEROFUNITTYPES + EUT_SPEARMAN]->setTexture(texturemanager->getTexture("p2spearman"));
		unitimages[EUT_NUMBEROFUNITTYPES + EUT_ARCHER]->setTexture(texturemanager->getTexture("p2archer"));

		healthsprite->setTexture(texturemanager->getTexture("health"));
		healthsprite->setPosition(unitspritepos.x + 52, unitspritepos.y);
		addWidget(healthsprite);

		unitattacksprite->setTexture(texturemanager->getTexture("attack"));
		unitattacksprite->setPosition(unitspritepos.x + 52, unitspritepos.y + 70);
		addWidget(unitattacksprite);

		unitdefensesprite->setTexture(texturemanager->getTexture("defense"));
		unitdefensesprite->setPosition(unitspritepos.x + 52, unitspritepos.y + 105);
		addWidget(unitdefensesprite);

		movementsprite->setTexture(texturemanager->getTexture("movement"));
		movementsprite->setPosition(unitspritepos.x + 52,unitspritepos.y + 35);
		addWidget(movementsprite);

		// set up sprites for terrain information
		sf::Vector2f terrainspritepos(630, 210);
		for(int i = 0; i < ET_NUMBEROFTERRAINTYPES; ++i)
		{
			terrainimages[i] = new namelessgui::SpriteWidget(guihandler->getRenderWindow(), 32, 32);
			terrainimages[i]->setPosition(terrainspritepos.x, terrainspritepos.y);
			terrainimages[i]->setScale(1.5, 1.5);
			this->addWidget(terrainimages[i]);
		}
		terrainimages[ET_WOOD]->setTexture(texturemanager->getTexture("wood"));
		terrainimages[ET_HILL]->setTexture(texturemanager->getTexture("hill"));
		terrainimages[ET_WALL]->setTexture(texturemanager->getTexture("wall"));

		terrainplainsquare->setTexture(texturemanager->getTexture("plainsquare"));
		terrainplainsquare->setPosition(terrainspritepos);
		terrainplainsquare->setScale(1.5, 1.5);
		addWidget(terrainplainsquare);

		terrainattacksprite->setTexture(texturemanager->getTexture("attack"));
		terrainattacksprite->setPosition(terrainspritepos.x + 52, terrainspritepos.y);
		addWidget(terrainattacksprite);

		terraindefensesprite->setTexture(texturemanager->getTexture("defense"));
		terraindefensesprite->setPosition(terrainspritepos.x + 52, terrainspritepos.y + 35);
		addWidget(terraindefensesprite);

		// Set up text widgets
		healthtext->setFont(*defaultfont);
		healthtext->setCharacterSize(30);
		healthtext->setPosition(unitspritepos.x + 90, unitspritepos.y - 3);
		addWidget(healthtext);

		unitmovementtext->setFont(*defaultfont);
		unitmovementtext->setCharacterSize(30);
		unitmovementtext->setPosition(unitspritepos.x + 90, unitspritepos.y + 32);
		addWidget(unitmovementtext);

		unitattacktext->setFont(*defaultfont);
		unitattacktext->setCharacterSize(30);
		unitattacktext->setPosition(unitspritepos.x + 90, unitspritepos.y + 64);
		addWidget(unitattacktext);

		unitdefensetext->setFont(*defaultfont);
		unitdefensetext->setCharacterSize(30);
		unitdefensetext->setPosition(unitspritepos.x + 90, unitspritepos.y + 98);
		addWidget(unitdefensetext);

		terrainattacktext->setFont(*defaultfont);
		terrainattacktext->setPosition(terrainspritepos.x + 90, terrainspritepos.y - 3);
		terrainattacktext->setCharacterSize(30);
		addWidget(terrainattacktext);

		terraindefensetext->setFont(*defaultfont);
		terraindefensetext->setPosition(terrainspritepos.x + 90, terrainspritepos.y + 32);
		terraindefensetext->setCharacterSize(30);
		addWidget(terraindefensetext);

		endturnbutton->setText("End turn!");
		endturnbutton->setTextures(texturemanager->getTexture("nextbutton"),
			texturemanager->getTexture("nextbutton_active"),
			texturemanager->getTexture("nextbutton_hover"));
		endturnbutton->setPosition(sf::Vector2f(700, 560));
		endturnbutton->setScale(sf::Vector2f(1, 1));
		endturnbutton->signalclicked.connect(std::bind(&IngameWindow::changeplayerbuttonClicked, this));
		addWidget(endturnbutton);
	}

	IngameWindow::~IngameWindow()
	{
		for(int i =  0; i < EUT_NUMBEROFUNITTYPES * 2; ++i)
			delete unitimages[i];

		for(int i = 0; i < ET_NUMBEROFTERRAINTYPES; ++i)
			delete terrainimages[i];

		delete unitplainsquare;
		delete healthsprite;
		delete unitattacksprite;
		delete unitdefensesprite;
		delete movementsprite;

		delete terrainplainsquare;
		delete terrainattacksprite;
		delete terraindefensesprite;

		delete defaultfont;

		delete healthtext;
		delete unitattacktext;
		delete unitdefensetext;
		delete unitmovementtext;
		delete terrainattacktext;
		delete terraindefensetext;
	}

	void IngameWindow::update()
	{
		// Update player name
		playernamelabel->setText(engine->getCurrentPlayer().getName());
		// Update Square information
		Board* board = engine->getBoard();
		Cursor* cursor = Cursor::getCursor()->getChild();
		if(cursor == NULL)
			cursor = Cursor::getCursor();

		Square* square = board->getSquare(cursor->getPosition().getX(), cursor->getPosition().getY());
		Unit* unit = square->getUnit();

		for(int i = 0; i < EUT_NUMBEROFUNITTYPES * 2; ++i)
			unitimages[i]->setVisible(false);
		for(int i = 0; i < ET_NUMBEROFTERRAINTYPES; ++i)
			terrainimages[i]->setVisible(false);

		// Decide which unit has to be drawn
		if(unit != NULL)
		{
			// Update text
			healthtext->setText(intToString(unit->getHP()) + " / " + intToString(unit->getMaxHp()));
			unitattacktext->setText(intToString(unit->getBaseAttack()));
			unitdefensetext->setText(intToString(unit->getBaseDefense()));
			unitmovementtext->setText(intToString(unit->getCurrentMovement()) + " / " + intToString(unit->getMovement()));

			unitimages[unit->getPlayer()->getId() * EUT_NUMBEROFUNITTYPES + unit->getType()]->setVisible(true);
		}
		else
		{
			unitattacktext->setText("");
			unitdefensetext->setText("");
			healthtext->setText("");
			unitmovementtext->setText("");
		}
		// Decide which terrain has to be drawn
		Terrain* terrain = square->getTerrain();
		if(terrain != NULL)
		{
			// Update terrain text
			terrainattacktext->setText(intToString(terrain->getModificator(EM_ATTACK)));
			terraindefensetext->setText(intToString(terrain->getModificator(EM_DEFENSE)));

			terrainimages[terrain->getType()]->setVisible(true);
		}
		else
		{
			terrainattacktext->setText("");
			terraindefensetext->setText("");
		}
	}

	void IngameWindow::changeplayerbuttonClicked()
	{
		if(engine->getStatus() == EES_RUNNING)
		{
			printf("IngameWindow: end turn\n");
			engine->endTurn();
			update();
		}
	}
}

