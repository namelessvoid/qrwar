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
	IngameWindow::IngameWindow(sf::RenderWindow* renderWindow, Engine* engine, GuiHandler* guihandler)
	: Window(renderWindow),
	  _engine(engine),
	  _guihandler(guihandler),
	  // TODO: Dynamic size
	  _endturnbutton(new namelessgui::Button(guihandler->getRenderWindow(), 100.0, 40.0)),
	  _playernamelabel(new namelessgui::Label(guihandler->getRenderWindow(), 100.0, 40.0)),

	  _unitplainsquare(new namelessgui::RectangularWidget(guihandler->getRenderWindow(), 32, 32)),
	  _healthsprite(new namelessgui::RectangularWidget(guihandler->getRenderWindow(), 32, 32)),
	  _unitattacksprite(new namelessgui::RectangularWidget(guihandler->getRenderWindow(), 32, 32)),
	  _unitdefensesprite(new namelessgui::RectangularWidget(guihandler->getRenderWindow(), 32, 32)),
	  _movementsprite(new namelessgui::RectangularWidget(guihandler->getRenderWindow(), 32, 32)),

	  _terrainplainsquare(new namelessgui::RectangularWidget(guihandler->getRenderWindow(), 32, 32)),
	  _terrainattacksprite(new namelessgui::RectangularWidget(guihandler->getRenderWindow(), 32, 32)),
	  _terraindefensesprite(new namelessgui::RectangularWidget(guihandler->getRenderWindow(), 32, 32)),

	  _defaultfont(new sf::Font()),

	  _healthtext(new namelessgui::Label(guihandler->getRenderWindow())),
	  _unitattacktext(new namelessgui::Label(guihandler->getRenderWindow())),
	  _unitdefensetext(new namelessgui::Label(guihandler->getRenderWindow())),
	  _unitmovementtext(new namelessgui::Label(guihandler->getRenderWindow())),
	  _terrainattacktext(new namelessgui::Label(guihandler->getRenderWindow())),
	  _terraindefensetext(new namelessgui::Label(guihandler->getRenderWindow()))
	{
		_defaultfont->loadFromFile("./res/font/Knigqst.ttf");
		_playernamelabel->setFont(*_defaultfont);
		_playernamelabel->setCharacterSize(25);
		_playernamelabel->setText("Player name");
		_playernamelabel->setPosition(625.0, 0.0);
		_playernamelabel->setColor(sf::Color::White);
		addWidget(_playernamelabel);

		TextureManager* texturemanager = TextureManager::getInstance();

		setPosition(620, 0);
		setSize(sf::Vector2f(200, 600));

		// set up sprites for unit information
		sf::Vector2f unitspritepos(630, 40);

		_unitplainsquare->setTexture(texturemanager->getTexture("plainsquare"));
		_unitplainsquare->setPosition(unitspritepos);
		_unitplainsquare->setScale(1.5, 1.5);
		addWidget(_unitplainsquare);

		for(int i =  0; i < EUT_NUMBEROFUNITTYPES * 2; ++i)
		{
			_unitimages[i] = new namelessgui::RectangularWidget(guihandler->getRenderWindow(), 32, 32);
			_unitimages[i]->setPosition(unitspritepos.x, unitspritepos.y);
			_unitimages[i]->setScale(1.5, 1.5);
			this->addWidget(_unitimages[i]);
			_unitimages[i]->setVisible(true);
		}
		_unitimages[EUT_SWORDMAN]->setTexture(texturemanager->getTexture("p1swordman"));
		_unitimages[EUT_SPEARMAN]->setTexture(texturemanager->getTexture("p1spearman"));
		_unitimages[EUT_ARCHER]->setTexture(texturemanager->getTexture("p1archer"));
		std::cout << EUT_NUMBEROFUNITTYPES * 2 - 1 << std::endl;
		_unitimages[EUT_NUMBEROFUNITTYPES + EUT_SWORDMAN]->setTexture(texturemanager->getTexture("p2swordman"));
		_unitimages[EUT_NUMBEROFUNITTYPES + EUT_SPEARMAN]->setTexture(texturemanager->getTexture("p2spearman"));
		_unitimages[EUT_NUMBEROFUNITTYPES + EUT_ARCHER]->setTexture(texturemanager->getTexture("p2archer"));

		_healthsprite->setTexture(texturemanager->getTexture("health"));
		_healthsprite->setPosition(unitspritepos.x + 52, unitspritepos.y);
		addWidget(_healthsprite);

		_unitattacksprite->setTexture(texturemanager->getTexture("attack"));
		_unitattacksprite->setPosition(unitspritepos.x + 52, unitspritepos.y + 70);
		addWidget(_unitattacksprite);

		_unitdefensesprite->setTexture(texturemanager->getTexture("defense"));
		_unitdefensesprite->setPosition(unitspritepos.x + 52, unitspritepos.y + 105);
		addWidget(_unitdefensesprite);

		_movementsprite->setTexture(texturemanager->getTexture("movement"));
		_movementsprite->setPosition(unitspritepos.x + 52,unitspritepos.y + 35);
		addWidget(_movementsprite);

		// set up sprites for terrain information
		sf::Vector2f terrainspritepos(630, 210);
		for(int i = 0; i < ET_NUMBEROFTERRAINTYPES; ++i)
		{
			_terrainimages[i] = new namelessgui::RectangularWidget(guihandler->getRenderWindow(), 32, 32);
			_terrainimages[i]->setPosition(terrainspritepos.x, terrainspritepos.y);
			_terrainimages[i]->setScale(1.5, 1.5);
			this->addWidget(_terrainimages[i]);
		}
		_terrainimages[ET_WOOD]->setTexture(texturemanager->getTexture("wood"));
		_terrainimages[ET_HILL]->setTexture(texturemanager->getTexture("hill"));
		_terrainimages[ET_WALL]->setTexture(texturemanager->getTexture("wall"));

		_terrainplainsquare->setTexture(texturemanager->getTexture("plainsquare"));
		_terrainplainsquare->setPosition(terrainspritepos);
		_terrainplainsquare->setScale(1.5, 1.5);
		addWidget(_terrainplainsquare);

		_terrainattacksprite->setTexture(texturemanager->getTexture("attack"));
		_terrainattacksprite->setPosition(terrainspritepos.x + 52, terrainspritepos.y);
		addWidget(_terrainattacksprite);

		_terraindefensesprite->setTexture(texturemanager->getTexture("defense"));
		_terraindefensesprite->setPosition(terrainspritepos.x + 52, terrainspritepos.y + 35);
		addWidget(_terraindefensesprite);

		// Set up text widgets
		_healthtext->setFont(*_defaultfont);
		_healthtext->setCharacterSize(30);
		_healthtext->setPosition(unitspritepos.x + 90, unitspritepos.y - 3);
		addWidget(_healthtext);

		_unitmovementtext->setFont(*_defaultfont);
		_unitmovementtext->setCharacterSize(30);
		_unitmovementtext->setPosition(unitspritepos.x + 90, unitspritepos.y + 32);
		addWidget(_unitmovementtext);

		_unitattacktext->setFont(*_defaultfont);
		_unitattacktext->setCharacterSize(30);
		_unitattacktext->setPosition(unitspritepos.x + 90, unitspritepos.y + 64);
		addWidget(_unitattacktext);

		_unitdefensetext->setFont(*_defaultfont);
		_unitdefensetext->setCharacterSize(30);
		_unitdefensetext->setPosition(unitspritepos.x + 90, unitspritepos.y + 98);
		addWidget(_unitdefensetext);

		_terrainattacktext->setFont(*_defaultfont);
		_terrainattacktext->setPosition(terrainspritepos.x + 90, terrainspritepos.y - 3);
		_terrainattacktext->setCharacterSize(30);
		addWidget(_terrainattacktext);

		_terraindefensetext->setFont(*_defaultfont);
		_terraindefensetext->setPosition(terrainspritepos.x + 90, terrainspritepos.y + 32);
		_terraindefensetext->setCharacterSize(30);
		addWidget(_terraindefensetext);

		_endturnbutton->setText("End turn!");
		_endturnbutton->setTextures(texturemanager->getTexture("nextbutton"),
			texturemanager->getTexture("nextbutton_active"),
			texturemanager->getTexture("nextbutton_hover"));
		_endturnbutton->setPosition(sf::Vector2f(700, 560));
		_endturnbutton->setScale(sf::Vector2f(1, 1));
		_endturnbutton->signalclicked.connect(std::bind(&IngameWindow::changeplayerbuttonClicked, this));
		addWidget(_endturnbutton);
	}

	IngameWindow::~IngameWindow()
	{
		for(int i =  0; i < EUT_NUMBEROFUNITTYPES * 2; ++i)
			delete _unitimages[i];

		for(int i = 0; i < ET_NUMBEROFTERRAINTYPES; ++i)
			delete _terrainimages[i];

		delete _unitplainsquare;
		delete _healthsprite;
		delete _unitattacksprite;
		delete _unitdefensesprite;
		delete _movementsprite;

		delete _terrainplainsquare;
		delete _terrainattacksprite;
		delete _terraindefensesprite;

		delete _defaultfont;

		delete _healthtext;
		delete _unitattacktext;
		delete _unitdefensetext;
		delete _unitmovementtext;
		delete _terrainattacktext;
		delete _terraindefensetext;
	}

	void IngameWindow::update()
	{
		// Update player name
		_playernamelabel->setText(_engine->getCurrentPlayer().getName());
		// Update Square information
		Board* board = _engine->getBoard();
		Cursor* cursor = Cursor::getCursor()->getChild();
		if(cursor == NULL)
			cursor = Cursor::getCursor();

		Square* square = board->getSquare(cursor->getPosition().getX(), cursor->getPosition().getY());
		Unit* unit = square->getUnit();

		for(int i = 0; i < EUT_NUMBEROFUNITTYPES * 2; ++i)
			_unitimages[i]->setVisible(false);
		for(int i = 0; i < ET_NUMBEROFTERRAINTYPES; ++i)
			_terrainimages[i]->setVisible(false);

		// Decide which unit has to be drawn
		if(unit != NULL)
		{
			// Update text
			_healthtext->setText(intToString(unit->getHP()) + " / " + intToString(unit->getMaxHp()));
			_unitattacktext->setText(intToString(unit->getBaseAttack()));
			_unitdefensetext->setText(intToString(unit->getBaseDefense()));
			_unitmovementtext->setText(intToString(unit->getCurrentMovement()) + " / " + intToString(unit->getMovement()));

			_unitimages[unit->getPlayer()->getId() * EUT_NUMBEROFUNITTYPES + unit->getType()]->setVisible(true);
		}
		else
		{
			_unitattacktext->setText("");
			_unitdefensetext->setText("");
			_healthtext->setText("");
			_unitmovementtext->setText("");
		}
		// Decide which terrain has to be drawn
		Terrain* terrain = square->getTerrain();
		if(terrain != NULL)
		{
			// Update terrain text
			_terrainattacktext->setText(intToString(terrain->getModificator(EM_ATTACK)));
			_terraindefensetext->setText(intToString(terrain->getModificator(EM_DEFENSE)));

			_terrainimages[terrain->getType()]->setVisible(true);
		}
		else
		{
			_terrainattacktext->setText("");
			_terraindefensetext->setText("");
		}
	}

	void IngameWindow::changeplayerbuttonClicked()
	{
		if(_engine->getStatus() == EES_RUNNING)
		{
			printf("IngameWindow: end turn\n");
			_engine->endTurn();
			update();
		}
	}
}

