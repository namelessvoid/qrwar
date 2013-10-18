#include "gui/boardwidget.hpp"

#include <cmath>

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>
#include <stdio.h>

#include "engine/engine.hpp"
#include "engine/player.hpp"
#include "gui/guihandler.hpp"
#include "gui/cursor.hpp"

namespace qrw
{
	BoardWidget::BoardWidget(GuiHandler* guihandler, Engine* engine, float width, float height)
	: Widget(guihandler->getRenderWindow(), width, height),
	  board(0),
	  engine(engine),
	  spritedimensions(0.0),
	  singlespritescale(0.0),
	  deploywindow(guihandler->getDeployWindow())
	{
		printf("boardrenderer position: x=%f / y=%f\n", getGlobalBounds().left, getGlobalBounds().top);
		printf("boardrenderer size: w=%f / h=%f\n", getSize().x, getSize().y);

		// Create required sprites.
		TextureManager* texturemanager = TextureManager::getInstance();

		plainsquare = new sf::Sprite(*texturemanager->getTexture("plainsquare"));
		terrainsprites[ET_WOOD] = new sf::Sprite(*texturemanager->getTexture("wood"));
		terrainsprites[ET_HILL] = new sf::Sprite(*texturemanager->getTexture("hill"));
		terrainsprites[ET_WALL] = new sf::Sprite(*texturemanager->getTexture("wall"));
		p1unitsprites[EUT_SWORDMAN] = new sf::Sprite(*texturemanager->getTexture("p1swordman"));
		p1unitsprites[EUT_ARCHER] = new sf::Sprite(*texturemanager->getTexture("p1archer"));
		p1unitsprites[EUT_SPEARMAN] = new sf::Sprite(*texturemanager->getTexture("p1spearman"));
		p2unitsprites[EUT_SWORDMAN] = new sf::Sprite(*texturemanager->getTexture("p2swordman"));
		p2unitsprites[EUT_ARCHER] = new sf::Sprite(*texturemanager->getTexture("p2archer"));
		p2unitsprites[EUT_SPEARMAN] = new sf::Sprite(*texturemanager->getTexture("p2spearman"));

		signalmousemoved.connect(std::bind(&BoardWidget::updateCursor, this));
		signalmouseentered.connect(std::bind(&BoardWidget::updateCursor, this));
	}

	BoardWidget::~BoardWidget()
	{
		delete plainsquare;
	}

	void BoardWidget::setBoard(Board* board)
	{
		this->board = board;
		calcSpriteDimensions(board->getWidth(), board->getHeight());
	}


	void BoardWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		sf::Vector2f targetsize = target.getView().getSize();
		targetsize.x -= 180.0;
		int width = board->getWidth();
		int height = board->getHeight();

		sf::Vector2f spritescale(singlespritescale, singlespritescale);
		sf::VertexArray vertices(sf::Lines, 0);
		Square *square = 0;
		Unit *unit = 0;
		Terrain *terrain = 0;
		sf::Vector2f currpos;

		sf::Vector2i cursorpos = Cursor::getCursor()->getPosition();
		sf::Vector2i childcursorpos(-1, -1);

		if(Cursor::getCursor()->getChild() != 0)
		{
			childcursorpos.x = Cursor::getCursor()->getChild()->getPosition().x;
			childcursorpos.y = Cursor::getCursor()->getChild()->getPosition().y;
		}

		for(int i = 0; i < width; ++i)
		{
			for(int j = 0; j < height; ++j)
			{
				currpos.x = i * spritedimensions;
				currpos.y = j * spritedimensions;

				plainsquare->setPosition(currpos);
				plainsquare->setScale(spritescale);
				target.draw(*plainsquare);

				square = board->getSquare(i, j);
				terrain = square->getTerrain();
				unit = square->getUnit();
				// Render cursor
				if(cursorpos.x == i && cursorpos.y == j)
					Cursor::getCursor()->draw(target, currpos, spritedimensions);
				if(childcursorpos.x == i && childcursorpos.y == j)
					Cursor::getCursor()->drawChild(target, currpos, spritedimensions);

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
	}

	void BoardWidget::calcSpriteDimensions(int boardwidth, int boardheight)
	{
		if(boardwidth > boardheight)
		{
			spritedimensions = getSize().x / boardwidth;
			singlespritescale = getSize().x / (boardwidth * 32.0);
		}
		else
		{
			spritedimensions = getSize().y / boardheight;
			singlespritescale = getSize().y / (boardheight * 32.0);
		}
	}

	void BoardWidget::drawTerrain(sf::RenderTarget& target,
		TERRAINTYPES terraintype, sf::Vector2f position, sf::Vector2f scale) const
	{
		terrainsprites[terraintype]->setPosition(position);
		terrainsprites[terraintype]->setScale(scale);
		target.draw(*terrainsprites[terraintype]);
	}

	void BoardWidget::drawUnit(sf::RenderTarget& target, int playerid,
		UNITTYPES unittype, sf::Vector2f position, sf::Vector2f scale) const
	{
		sf::Sprite* unitsprite = 0;
		if(playerid == 0)
			unitsprite = p1unitsprites[unittype];
		else
			unitsprite = p2unitsprites[unittype];
		unitsprite->setPosition(position);
		unitsprite->setScale(scale);
		target.draw(*unitsprite);
	}

	void BoardWidget::updateCursor()
	{
		// Calculate on which field the mouse cursor is placed.
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
		sf::Vector2i newCursorPos;

		newCursorPos.x = floor( ((float)mousePosition.x) / spritedimensions );
		newCursorPos.y = floor( ((float)mousePosition.y) / spritedimensions );

		// Boarder checks
		if(newCursorPos.x < 0)
			newCursorPos.x = 0;
		else if(newCursorPos.x > board->getWidth())
			newCursorPos.x = board->getWidth();

		if(newCursorPos.y < 0)
			newCursorPos.y = 0;
		else if(newCursorPos.y > board->getHeight())
			newCursorPos.y = board->getHeight();

		if(!Cursor::getCursor()->getChild())
			Cursor::getCursor()->setPosition(newCursorPos);
		else
			Cursor::getCursor()->getChild()->setPosition(newCursorPos);
	}
}