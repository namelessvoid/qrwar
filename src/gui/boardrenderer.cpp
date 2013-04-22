#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>
#include <stdio.h>

#include "gui/boardrenderer.hpp"
#include "gui/cursor.hpp"

namespace qrw
{
	BoardRenderer::BoardRenderer()
	:	board(0),
		texturemanager(TextureManager::getInstance())
	{	
		// Load all required textures
		// plain square
		texturemanager.loadTexture("plainsquare", "./res/img/plainsquare.png");
		// units
		texturemanager.loadTexture("swordman", "./res/img/units/swordman.png");
		texturemanager.loadTexture("archer", "./res/img/units/archer.png");
		texturemanager.loadTexture("spearman", "./res/img/units/spearman.png");
		// terrain
		texturemanager.loadTexture("wood", "./res/img/terrain/wood.png");
		texturemanager.loadTexture("hill", "./res/img/terrain/hill.png");

		plainsquare = new sf::Sprite(*texturemanager.getTexture("plainsquare"));
		terrainsprites[ET_WOOD] = new sf::Sprite(*texturemanager.getTexture("wood"));
		terrainsprites[ET_HILL] = new sf::Sprite(*texturemanager.getTexture("hill"));
		unitsprites[EUT_SWORDMAN] = new sf::Sprite(*texturemanager.getTexture("swordman"));
	}

	BoardRenderer::~BoardRenderer()
	{
		delete plainsquare;
	}

	void BoardRenderer::setBoard(Board* board)
	{
		this->board = board;
	}

	void BoardRenderer::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		sf::Vector2f targetsize = target.getView().getSize();
		targetsize.x -= 180.0;
		int width = board->getWidth();
		int height = board->getHeight();
		float spritedimensions;
		float singlespritescale = 1.0;

		if(width > height)
		{
			spritedimensions = targetsize.x / width;
			singlespritescale = targetsize.x / (width * 32.0);
		}
		else
		{
			spritedimensions = targetsize.y / height;
			singlespritescale = targetsize.y / (height * 32.0);
		}

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
					if(terrain->getType() == ET_WOOD)
					{
						terrainsprites[ET_WOOD]->setPosition(currpos);
						terrainsprites[ET_WOOD]->setScale(spritescale);
						target.draw(*terrainsprites[ET_WOOD]);
					}
					else if(terrain->getType() == ET_HILL)
					{
						terrainsprites[ET_HILL]->setPosition(currpos);
						terrainsprites[ET_HILL]->setScale(spritescale);
						target.draw(*terrainsprites[ET_HILL]);
					}
				}
				// Render Units
				if(unit != 0)
				{
					if(unit->getType() == EUT_SWORDMAN)
					{
						unitsprites[EUT_SWORDMAN]->setPosition(currpos);
						unitsprites[EUT_SWORDMAN]->setScale(spritescale);
						target.draw(*unitsprites[EUT_SWORDMAN]);
					}
				}
			}
		}
	}
}