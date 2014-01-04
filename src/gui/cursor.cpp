#include <stdio.h>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "gui/cursor.hpp"

namespace qrw
{
	Cursor* Cursor::cursor = 0;

	Cursor::Cursor()
	: RectangleShape(),
	  position(0, 0),
	  child(0),
	  maincolor(218, 218, 0, 120),
	  subcolor(218, 0, 0, 120)
	{
		setFillColor(maincolor);
	}

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

		RectangleShape::setPosition(x * dimensions, y * dimensions);
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

	void Cursor::setDimensions(float dimensions)
	{
		this->dimensions = dimensions;
		RectangleShape::setSize(sf::Vector2f(dimensions, dimensions));
	}

	Cursor* Cursor::spawnChild()
	{
		if(child != 0)
			return 0;
		else
		{
			child = new Cursor();
			child->setBoard(board);
			child->setDimensions(dimensions);
			child->setPosition(position);
			child->setFillColor(maincolor);
			this->setFillColor(subcolor);
		}
		return child;
	}

	Cursor* Cursor::getChild() const
	{
		return child;
	}

	void Cursor::despawnChild()
	{
		if(child != 0)
		{
			delete child;
			child = 0;
			this->setFillColor(maincolor);
		}
	}

	void Cursor::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw((sf::RectangleShape)*this, states);
		if(getChild() != 0)
			target.draw(*getChild(), states);
	}
}