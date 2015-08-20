#include "gui/boardwidget.hpp"

#include <cmath>

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transform.hpp>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

#include <iostream>
#include <stdio.h>

#include "engine/engine.hpp"
#include "engine/unit.hpp"
#include "engine/terrain.hpp"
#include "engine/player.hpp"
#include "engine/board.hpp"
#include "engine/square.hpp"
#include "engine/pathfinding/path.hpp"

#include "gui/texturemanager.hpp"
#include "gui/guihandler.hpp"
#include "gui/cursor.hpp"
#include "gui/damagenumber.hpp"
#include "gui/deploywindow.hpp"

namespace qrw
{
	BoardWidget::BoardWidget(GuiHandler* guihandler, Engine* engine, float width, float height)
	: Widget(guihandler->getRenderWindow(), width, height),
	  _engine(engine),
	  _board(0),
	  _spritedimensions(0.0),
	  _singlespritescale(0.0),
	  _path(0),
	  _deploywindow(guihandler->getDeployWindow())
	{
		printf("boardrenderer position: x=%f / y=%f\n", getGlobalBounds().left, getGlobalBounds().top);
		printf("boardrenderer size: w=%f / h=%f\n", getSize().x, getSize().y);

		// Create required sprites.
		TextureManager* texturemanager = TextureManager::getInstance();

		_plainsquare = new sf::Sprite(*texturemanager->getTexture("plainsquare"));
		_footstep = new sf::Sprite(*texturemanager->getTexture("footstep"));
		_terrainsprites[ET_WOOD] = new sf::Sprite(*texturemanager->getTexture("wood"));
		_terrainsprites[ET_HILL] = new sf::Sprite(*texturemanager->getTexture("hill"));
		_terrainsprites[ET_WALL] = new sf::Sprite(*texturemanager->getTexture("wall"));
		_p1unitsprites[EUT_SWORDMAN] = new sf::Sprite(*texturemanager->getTexture("p1swordman"));
		_p1unitsprites[EUT_ARCHER] = new sf::Sprite(*texturemanager->getTexture("p1archer"));
		_p1unitsprites[EUT_SPEARMAN] = new sf::Sprite(*texturemanager->getTexture("p1spearman"));
		_p2unitsprites[EUT_SWORDMAN] = new sf::Sprite(*texturemanager->getTexture("p2swordman"));
		_p2unitsprites[EUT_ARCHER] = new sf::Sprite(*texturemanager->getTexture("p2archer"));
		_p2unitsprites[EUT_SPEARMAN] = new sf::Sprite(*texturemanager->getTexture("p2spearman"));

		signalmousemoved.connect(std::bind(&BoardWidget::updateCursor, this));
		signalmouseentered.connect(std::bind(&BoardWidget::updateCursor, this));
		signalclicked.connect(std::bind(&BoardWidget::leftClicked, this));
		signalrightclicked.connect(std::bind(&BoardWidget::rightClicked, this));
	}

	BoardWidget::~BoardWidget()
	{
		for(int i = 0; i < ET_NUMBEROFTERRAINTYPES; ++i)
			delete _terrainsprites[i];

		for(int i = 0; i < EUT_NUMBEROFUNITTYPES; ++i)
		{
			delete _p1unitsprites[i];
			delete _p2unitsprites[i];
		}

		delete _plainsquare;
		delete _footstep;
	}

	void BoardWidget::setBoard(Board* board)
	{
		this->_board = board;
		calcSpriteDimensions(board->getWidth(), board->getHeight());
	}


	void BoardWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		sf::Vector2f targetsize = target.getView().getSize();
		targetsize.x -= 180.0;
		int width = _board->getWidth();
		int height = _board->getHeight();

		sf::Vector2f spritescale(_singlespritescale, _singlespritescale);
		Square *square = 0;
		Unit *unit = 0;
		Terrain *terrain = 0;
		sf::Vector2f currpos;

		Coordinates childcursorpos(-1, -1);

		if(Cursor::getCursor()->getChild() != 0)
		{
			childcursorpos = Cursor::getCursor()->getChild()->getPosition();
		}

		for(int i = 0; i < width; ++i)
		{
			for(int j = 0; j < height; ++j)
			{
				currpos.x = i * _spritedimensions;
				currpos.y = j * _spritedimensions;

				_plainsquare->setPosition(currpos);
				_plainsquare->setScale(spritescale);
				target.draw(*_plainsquare);

				square = _board->getSquare(i, j);
				terrain = square->getTerrain();
				unit = square->getUnit();

				// Render Terrain
				if(terrain != 0)
				{
					drawTerrain(target, terrain->getType(), currpos, spritescale);
				}
				// Render Units
				if(unit != 0)
				{
					drawUnit(target, unit->getPlayer()->getId(), unit->getType(),
						currpos, spritescale);
				}
			}
		}

		// Render cursor
		Cursor* cursor = Cursor::getCursor();
		cursor->setDimensions(_spritedimensions);
		target.draw(*cursor, states);

		drawPath(target, spritescale);
	}

	void BoardWidget::calcSpriteDimensions(int boardwidth, int boardheight)
	{
		if(boardwidth > boardheight)
		{
			_spritedimensions = getSize().x / boardwidth;
			_singlespritescale = getSize().x / (boardwidth * 32.0);
		}
		else
		{
			_spritedimensions = getSize().y / boardheight;
			_singlespritescale = getSize().y / (boardheight * 32.0);
		}
	}

	void BoardWidget::drawTerrain(sf::RenderTarget& target,
		TERRAINTYPES terraintype, sf::Vector2f position, sf::Vector2f scale) const
	{
		_terrainsprites[terraintype]->setPosition(position);
		_terrainsprites[terraintype]->setScale(scale);
		target.draw(*_terrainsprites[terraintype]);
	}

	void BoardWidget::drawUnit(sf::RenderTarget& target, int playerid,
		UNITTYPES unittype, sf::Vector2f position, sf::Vector2f scale) const
	{
		sf::Sprite* unitsprite = 0;
		if(playerid == 0)
			unitsprite = _p1unitsprites[unittype];
		else
			unitsprite = _p2unitsprites[unittype];
		unitsprite->setPosition(position);
		unitsprite->setScale(scale);
		target.draw(*unitsprite);
	}

	void BoardWidget::drawPath(sf::RenderTarget& target, sf::Vector2f scale) const
	{
		if(!_path)
			return;

		int pathlength = _path->getLength();

		Square* previous = 0;
		Square* current  = _path->getStep(0);
		Square* next     = _path->getStep(1);

		// Do not render first step.
		for(int i = 1; i < pathlength; ++i)
		{
			previous = current;
			current  = next;

			// Reset the previously applied transformations.
			_footstep->setOrigin(16, 16);
			_footstep->setScale(scale);
			_footstep->setRotation(0);

			// Transformations relative to the previous step
			Coordinates prevdelta(previous->getCoordinates() - current->getCoordinates());
			if(prevdelta.getX() != 0)
				_footstep->rotate(-90 * prevdelta.getX());
			if(prevdelta.getY() != 0)
				_footstep->scale(1, prevdelta.getY());

			// Transformations relative to the next step (if possible)
			if(i < pathlength - 1)
			{
				next = _path->getStep(i+1);

				Coordinates prevnextdelta(previous->getCoordinates() - next->getCoordinates());

				// If the path has a corner at this position
				if(prevnextdelta.getX() != 0 && prevnextdelta.getY() != 0)
				{
					int rotationdirection = 0;
					// horizontal
					if(prevdelta.getX() == 0)
					{
						rotationdirection = -1;
					}
					// vertical
					else if(prevdelta.getY() == 0)
					{
						rotationdirection = +1;
					}
					_footstep->rotate(rotationdirection * 45 * (prevnextdelta.getX() * prevnextdelta.getY()));
				}
			}

			_footstep->setPosition(
				_spritedimensions * (0.5f + current->getXPosition()),
				_spritedimensions * (0.5f + current->getYPosition())
			);

			target.draw(*_footstep);
		}
	}

	void BoardWidget::moveUnitIngame()
	{
		Cursor* cursor = Cursor::getCursor();
		Cursor* childcursor = cursor->getChild();

		if(childcursor)
		{
			Unit* unit1 = _board->getSquare(cursor->getPosition())->getUnit();
			Unit* unit2 = _board->getSquare(childcursor->getPosition())->getUnit();

			// Simple move
			if(!unit2)
			{
				unit1->moveTo(childcursor->getPosition());
			}
			// unit 2 is present: attack
			else
			{
				Unit::AttackResult attackResult = unit1->attack(unit2);

				if(attackResult.attackPerformed)
				{
					DamageNumber* dm;
					sf::Vector2f pos;

					// First DMG number
					pos.x = cursor->getPosition().getX() * _spritedimensions;
					pos.y = cursor->getPosition().getY() * _spritedimensions + _spritedimensions * 0.2;
					dm = new DamageNumber(attackResult.attackerHPDelta, pos);

					// Second DMG number
					pos.x = childcursor->getPosition().getX() * _spritedimensions;
					pos.y = childcursor->getPosition().getY() * _spritedimensions + _spritedimensions * 0.2;
					dm = new DamageNumber(attackResult.defenderHPDelta, pos);
				}
			}

			// Resetting cursors
			cursor->setPosition(childcursor->getPosition());
			cursor->despawnChild();
			// Reset path
			if(_path)
			{
				delete _path;
				_path = 0;
			}
		} // if(childcursor)
	}


	void BoardWidget::updateCursor()
	{
		// Calculate on which field the mouse cursor is placed.
		sf::Vector2i mousePixelPosition = sf::Mouse::getPosition(*(sf::Window*)_window);
		sf::Vector2f mouseWorldPosition = _window->mapPixelToCoords(mousePixelPosition);
		sf::Vector2i newCursorPos;

		newCursorPos.x = floor( mouseWorldPosition.x / _spritedimensions );
		newCursorPos.y = floor( mouseWorldPosition.y / _spritedimensions );

		// Border checks
		if(newCursorPos.x < 0)
			newCursorPos.x = 0;
		else if(newCursorPos.x > _board->getWidth())
			newCursorPos.x = _board->getWidth();

		if(newCursorPos.y < 0)
			newCursorPos.y = 0;
		else if(newCursorPos.y > _board->getHeight())
			newCursorPos.y = _board->getHeight();

		if(!Cursor::getCursor()->getChild())
			Cursor::getCursor()->setPosition(newCursorPos);
		else
		{
			Coordinates oldCoordinates = Cursor::getCursor()->getChild()->getPosition();

			Cursor::getCursor()->getChild()->setPosition(newCursorPos);

			if(_engine->getStatus() == EES_RUNNING && oldCoordinates != Coordinates(newCursorPos.x, newCursorPos.y))
			{
				// Update path
				if(_path)
					delete _path;
				_path = _board->findPath(
					Coordinates(Cursor::getCursor()->getPosition()),
					Coordinates(newCursorPos.x, newCursorPos.y)
				);
			}
		}
	}

	void BoardWidget::leftClicked()
	{
		Cursor* cursor = Cursor::getCursor();
		Cursor* childcursor = cursor->getChild();
		Square* cursorsquare = _board->getSquare(cursor->getPosition());

		// Depploy unit / terrain by calling deploywindow methods.
		if(_engine->getStatus() == EES_PREPARE)
		{
			if(childcursor)
			{
				_deploywindow->moveUnit();
			}
			else if(cursorsquare->getUnit())
			{
				cursor->spawnChild();
			}
			else
			{
				printf("boardwidget leftclicked pre placeEntity (deploywindow=%p)\n", _deploywindow);
				_deploywindow->placeEntity();
			}
		}
		// Ingame actions.
		// TODO: Following code is just a copy&paste of GuiHandler::HandleEvent() code. Find a better solution
		// for this code duplication...
		else
		{
			if(cursorsquare->getUnit() && !childcursor)
			{
				cursor->spawnChild();
			}
			// Move a unit
			else if(childcursor)
			{
				this->moveUnitIngame();
			}
		}
	} // BoardWidget::leftClicked();

	void BoardWidget::rightClicked()
	{
		Cursor* cursor = Cursor::getCursor();
		Cursor* childcursor = cursor->getChild();
		if(childcursor)
		{
			cursor->setPosition(childcursor->getPosition());
			cursor->despawnChild();
		}
		if(_path)
		{
			delete _path;
			_path = 0;
		}
	}
}
