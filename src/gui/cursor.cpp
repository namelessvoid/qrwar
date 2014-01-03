#include <stdio.h>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>
// #include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "gui/cursor.hpp"

namespace qrw
{
	Cursor* Cursor::cursor = 0;

	Cursor::Cursor()
	: position(0, 0),
	  child(0)
	{}

	Cursor::~Cursor()
	{}

	Cursor* Cursor::getCursor()
	{
		if(cursor == 0)
			cursor = new Cursor();
		return cursor;
	}

	void Cursor::setBoard(Board* board)
	{
		this->board = board;
	}

	bool Cursor::move(int dx, int dy)
	{
		if(child != 0)
		{
			return child->move(dx, dy);
		}
		if(board == 0)
			return false;
		if(board->getSquare(position) == 0)
			return false;
		setPosition(position.getX() + dx, position.getY() + dy);
		return true;
	}

	bool Cursor::setPosition(int x, int y)
	{
		if(board == 0)
			return false;
		if(board->getSquare(x, y) == 0)
			return false;
		position = Coordinates(x, y);
		return true;
	}

	bool Cursor::setPosition(sf::Vector2i pos)
	{
		return setPosition(pos.x, pos.y);
	}

	bool Cursor::setPosition(Coordinates pos)
	{
		return setPosition(pos.getX(), pos.getY());
	}

	const Coordinates& Cursor::getPosition() const
	{
		return position;
	}

	Cursor* Cursor::spawnChild()
	{
		if(child != 0)
			return 0;
		else
		{
			child = new Cursor();
			child->setBoard(board);
			child->setPosition(position);
		}
		return child;
	}

	Cursor* Cursor::getChild()
	{
		return child;
	}

	void Cursor::despawnChild()
	{
		if(child != 0)
		{
			delete child;
			child = 0;
		}
	}

	void Cursor::draw(sf::RenderTarget& target, sf::Vector2f position, float size)
	{
		sf::Color col(218, 0, 0, 120);
		// Change color if child is present
		if(getChild() == 0)
			col += sf::Color(0, 218, 0, 0);
		sf::VertexArray quad(sf::Quads);
		quad.append(sf::Vertex(sf::Vector2f(position.x, position.y), col));
		quad.append(sf::Vertex(sf::Vector2f(position.x + size, position.y), col));
		quad.append(sf::Vertex(sf::Vector2f(position.x + size, position.y + size), col));
		quad.append(sf::Vertex(sf::Vector2f(position.x, position.y + size), col));
		target.draw(quad);
	}

	void Cursor::drawChild(sf::RenderTarget& target, sf::Vector2f position, float size)
	{
		if(getChild())
		{
			sf::Color col(218, 218, 0, 120);
			sf::VertexArray quad(sf::Quads);
			quad.append(sf::Vertex(sf::Vector2f(position.x, position.y), col));
			quad.append(sf::Vertex(sf::Vector2f(position.x + size, position.y), col));
			quad.append(sf::Vertex(sf::Vector2f(position.x + size, position.y + size), col));
			quad.append(sf::Vertex(sf::Vector2f(position.x, position.y + size), col));
			target.draw(quad);
		}
	}
}