#include <stdio.h>

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

	sf::Vector2i Cursor::getPosition()
	{
		return position;
	}

	bool Cursor::move(int dx, int dy)
	{
		if(child != 0)
		{
			return child->move(dx, dy);
		}
		if(board == 0)
			return false;
		if(board->getSquare(position.x + dx, position.y + dy) == 0)
			return false;
		position.x += dx;
		position.y += dy;
		return true;
	}

	bool Cursor::setPosition(int x, int y)
	{
		if(board == 0)
			return false;
		if(board->getSquare(x, y) == 0)
			return false;
		position.x = x;
		position.y = y;
		return true;
	}

	Cursor* Cursor::spawnChild()
	{
		if(child != 0)
			return 0;
		else
		{
			child = new Cursor();
			child->setBoard(board);
			child->setPosition(position.x, position.y);
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
}