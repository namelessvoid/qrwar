#include <stdio.h>

#include <SFGUI/Button.hpp>
#include <SFGUI/Table.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/Separator.hpp>

#include "tostring.hpp"
#include "gui/ingamewindow.hpp"
#include "gui/cursor.hpp"
#include "gui/imagemanager.hpp"
#include "gui/texturemanager.hpp"
#include "gui/guihandler.hpp"

namespace qrw
{
	IngameWindow::IngameWindow(Engine* engine, GuiHandler* guihandler)
	: engine(engine),
	  guihandler(guihandler),
	  // TODO: Dynamic size
	  endturnbutton(guihandler->getRenderWindow(), 100.0, 40.0),
	  playernamelabel(),

	  unitsprite(new sf::Sprite()),
	  terrainsprite(new sf::Sprite()),
	  plainsquare(new sf::Sprite()),

	  healthsprite(new sf::Sprite()),
	  attacksprite(new sf::Sprite()),
	  defensesprite(new sf::Sprite()),
	  movementsprite(new sf::Sprite()),

	  defaultfont(new sf::Font()),

	  healthtext(new sf::Text()),
	  unitattacktext(new sf::Text()),
	  unitdefensetext(new sf::Text()),
	  unitmovementtext(new sf::Text()),
	  terrainattacktext(new sf::Text()),
	  terraindefensetext(new sf::Text()),

	  background(new sf::RectangleShape()),
	  border(new sf::RectangleShape())
	{
		defaultfont->loadFromFile("./res/font/Knigqst.ttf");
		playernamelabel.setFont(*defaultfont);
		playernamelabel.setCharacterSize(25);
		playernamelabel.setString("Player name");
		playernamelabel.setPosition(sf::Vector2f(625, 0));
		playernamelabel.setColor(sf::Color::White);

		TextureManager* texturemanager = TextureManager::getInstance();

		healthsprite->setTexture(*texturemanager->getTexture("health"));
		attacksprite->setTexture(*texturemanager->getTexture("attack"));
		defensesprite->setTexture(*texturemanager->getTexture("defense"));

		background->setPosition(621, 1);
		background->setSize(sf::Vector2f(178, 598));
		background->setFillColor(sf::Color(40, 40, 40, 255));

		border->setPosition(620, 0);
		border->setSize(sf::Vector2f(180, 600));
		border->setFillColor(sf::Color(50, 70, 50, 255));

		unitsprite->setTexture(*texturemanager->getTexture("p1swordman"));
		unitsprite->setPosition(630, 40);
		unitsprite->setScale(sf::Vector2f(1.5, 1.5));

		terrainsprite->setTexture(*texturemanager->getTexture("wood"));
		terrainsprite->setPosition(630, 175);
		terrainsprite->setScale(sf::Vector2f(1.5, 1.5));

		plainsquare->setTexture(*texturemanager->getTexture("plainsquare"));
		plainsquare->setPosition(unitsprite->getPosition());

		healthtext->setFont(*defaultfont);
		healthtext->setCharacterSize(30);
		healthtext->setPosition(unitsprite->getPosition().x + 90, unitsprite->getPosition().y - 3);

		unitattacktext->setFont(*defaultfont);
		unitattacktext->setCharacterSize(30);
		unitattacktext->setPosition(unitsprite->getPosition().x + 90, unitsprite->getPosition().y + 32);

		unitdefensetext->setFont(*defaultfont);
		unitdefensetext->setCharacterSize(30);
		unitdefensetext->setPosition(unitsprite->getPosition().x + 90, unitsprite->getPosition().y + 64);

		terrainattacktext->setFont(*defaultfont);
		terrainattacktext->setPosition(terrainsprite->getPosition().x + 90, terrainsprite->getPosition().y - 3);
		terrainattacktext->setCharacterSize(30);

		terraindefensetext->setFont(*defaultfont);
		terraindefensetext->setPosition(terrainsprite->getPosition().x + 90, terrainsprite->getPosition().y + 32);
		terraindefensetext->setCharacterSize(30);

		endturnbutton.setText("End turn!");
		endturnbutton.setTextures(texturemanager->getTexture("nextbutton"),
			texturemanager->getTexture("nextbutton_active"),
			texturemanager->getTexture("nextbutton_hover"));
		endturnbutton.setPosition(sf::Vector2f(700, 560));
		endturnbutton.setScale(sf::Vector2f(1, 1));
		endturnbutton.signalclicked.connect(std::bind(&IngameWindow::changeplayerbuttonClicked, this));
		addWidget(&endturnbutton);
	}

	IngameWindow::~IngameWindow()
	{
			delete unitsprite;
			delete terrainsprite;
			delete plainsquare;

			delete healthsprite;
			delete attacksprite;
			delete defensesprite;
			delete movementsprite;

			delete defaultfont;

			delete healthtext;
			delete unitattacktext;
			delete unitdefensetext;
			delete unitmovementtext;
			delete terrainattacktext;
			delete terraindefensetext;

			delete background;
			delete border;
	}

	void IngameWindow::update()
	{
		// Update player name
		playernamelabel.setString(engine->getCurrentPlayer().getName());
		// Update Square information
		Board* board = engine->getBoard();
		Cursor* cursor = Cursor::getCursor()->getChild();
		if(cursor == NULL)
			cursor = Cursor::getCursor();

		Square* square = board->getSquare(cursor->getPosition().x, cursor->getPosition().y);
		Unit* unit = square->getUnit();

		// Decide which unit has to be drawn
		if(unit != NULL)
		{
			// Update text
			healthtext->setString(intToString(unit->getHP()));
			unitattacktext->setString(intToString(unit->getAttack()));
			unitdefensetext->setString(intToString(unit->getDefense()));
			// player 0 units
			if(unit->getPlayer() == engine->getPlayer(0))
			{
				switch(unit->getType())
				{
					case EUT_SWORDMAN:
						unitsprite->setTexture(*TextureManager::getInstance()->getTexture("p1swordman"));
						break;
					case EUT_ARCHER:
						unitsprite->setTexture(*TextureManager::getInstance()->getTexture("p1archer"));
						break;
					case EUT_SPEARMAN:
						unitsprite->setTexture(*TextureManager::getInstance()->getTexture("p1spearman"));
						break;
					default:
						break;
				}
			}
			// player 2 units
			else
			{
				switch(unit->getType())
				{
					case EUT_SWORDMAN:
						unitsprite->setTexture(*TextureManager::getInstance()->getTexture("p2swordman"));
						break;
					case EUT_ARCHER:
						unitsprite->setTexture(*TextureManager::getInstance()->getTexture("p2archer"));
						break;
					case EUT_SPEARMAN:
						unitsprite->setTexture(*TextureManager::getInstance()->getTexture("p2spearman"));
						break;
					default:
						break;
				}
			}
		}
		else
		{
			unitsprite->setTexture(*TextureManager::getInstance()->getTexture("plainsquare"));
			unitattacktext->setString("");
			unitdefensetext->setString("");
			healthtext->setString("");
		}
		// Decide which terrain has to be drawn
		Terrain* terrain = square->getTerrain();
		if(terrain != NULL)
		{
			// Update terrain text
			terrainattacktext->setString(intToString(terrain->getModificator(EM_ATTACK)));
			terraindefensetext->setString(intToString(terrain->getModificator(EM_DEFENSE)));
			// set terrain sprite
			switch(terrain->getType())
			{
				case ET_HILL:
					terrainsprite->setTexture(*TextureManager::getInstance()->getTexture("hill"));
					break;
				case ET_WOOD:
					terrainsprite->setTexture(*TextureManager::getInstance()->getTexture("wood"));
					break;
				case ET_WALL:
					terrainsprite->setTexture(*TextureManager::getInstance()->getTexture("wall"));
					break;
				default:
					break;
			}
		}
		else
		{
			terrainsprite->setTexture(*TextureManager::getInstance()->getTexture("plainsquare"));
			terrainattacktext->setString("");
			terraindefensetext->setString("");
		}
	}

	sf::Vector2f IngameWindow::getSize()
	{
		return sf::Vector2f(0, 0);
	}

	void IngameWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if(isVisible() == false)
			return;

		target.draw(*border);
		target.draw(*background);

		Window::draw(target, states);

		target.draw(playernamelabel);
		// Draw unit info
		sf::Vector2f pos = unitsprite->getPosition();
		plainsquare->setPosition(pos);
		plainsquare->setScale(unitsprite->getScale());
		target.draw(*plainsquare);
		if(unitsprite != NULL)
			target.draw(*unitsprite);
		healthsprite->setPosition(pos.x + 52, pos.y);
		attacksprite->setPosition(pos.x + 52, pos.y + 35);
		defensesprite->setPosition(pos.x + 52, pos.y + 70);
		target.draw(*healthsprite);
		target.draw(*attacksprite);
		target.draw(*defensesprite);
		target.draw(*healthtext);
		target.draw(*unitattacktext);
		target.draw(*unitdefensetext);

		// Draw terrain info
		pos = terrainsprite->getPosition();
		plainsquare->setPosition(pos);
		plainsquare->setScale(terrainsprite->getScale());
		target.draw(*plainsquare);
		if(terrainsprite != NULL)
			target.draw(*terrainsprite);
		attacksprite->setPosition(pos.x + 52, pos.y);
		defensesprite->setPosition(pos.x + 52, pos.y + 35);
		target.draw(*attacksprite);
		target.draw(*defensesprite);
		target.draw(*terrainattacktext);
		target.draw(*terraindefensetext);
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

