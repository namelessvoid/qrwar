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
		texturemanager.loadTexture("swordsman", "./res/img/units/swordsman.png");
		texturemanager.loadTexture("archer", "./res/img/units/archer.png");
		texturemanager.loadTexture("spearman", "./res/img/units/spearman.png");
		// terrain
		texturemanager.loadTexture("wood", "./res/img/terrain/wood.png");
		texturemanager.loadTexture("hill", "./res/img/terrain/hill.png");

		plainsquare = new sf::Sprite(*texturemanager.getTexture("plainsquare"));
		terrainsprites[0] = new sf::Sprite(*texturemanager.getTexture("wood"));
		terrainsprites[1] = new sf::Sprite(*texturemanager.getTexture("hill"));
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
				// Render selection
				if(cursorpos.x == i && cursorpos.y == j)
				{
					sf::Color col(218, 0, 0, 120);
					// Change color if child is present
					if(Cursor::getCursor()->getChild() == 0)
						col += sf::Color(0, 218, 0, 0);
					sf::VertexArray quad(sf::Quads);
					quad.append(sf::Vertex(currpos, col));
					quad.append(sf::Vertex(sf::Vector2f(currpos.x + spritedimensions, currpos.y), col));
					quad.append(sf::Vertex(sf::Vector2f(currpos.x + spritedimensions, currpos.y + spritedimensions), col));
					quad.append(sf::Vertex(sf::Vector2f(currpos.x, currpos.y + spritedimensions), col));
					target.draw(quad);
				}
				if(childcursorpos.x == i && childcursorpos.y == j)
				{
					sf::Color col(218, 218, 0, 120);
					sf::VertexArray quad(sf::Quads);
					quad.append(sf::Vertex(currpos, col));
					quad.append(sf::Vertex(sf::Vector2f(currpos.x + spritedimensions, currpos.y), col));
					quad.append(sf::Vertex(sf::Vector2f(currpos.x + spritedimensions, currpos.y + spritedimensions), col));
					quad.append(sf::Vertex(sf::Vector2f(currpos.x, currpos.y + spritedimensions), col));
					target.draw(quad);
				}
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
			}
		}
	}
}