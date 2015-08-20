#include <stdio.h>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "gui/cursor.hpp"
#include "engine/board.hpp"

namespace qrw
{
	Cursor* Cursor::_cursor = 0;

	Cursor::Cursor()
	: RectangleShape(),
	  _child(0),
	  _maincolor(218, 218, 0, 120),
	  _subcolor(218, 0, 0, 120),
	  _position(0, 0)
	{
		setFillColor(_maincolor);
	}

	Cursor::~Cursor()
	{}

	Cursor* Cursor::getCursor()
	{
		if(_cursor == 0)
			_cursor = new Cursor();
		return _cursor;
	}

	void Cursor::setBoard(Board* board)
	{
		this->_board = board;
	}

	bool Cursor::move(int dx, int dy)
	{
		if(_child != 0)
		{
			return _child->move(dx, dy);
		}
		if(_board == 0)
			return false;
		if(_board->getSquare(_position) == 0)
			return false;
		setPosition(_position.getX() + dx, _position.getY() + dy);
		return true;
	}

	bool Cursor::setPosition(int x, int y)
	{
		if(_board == 0)
			return false;
		if(_board->getSquare(x, y) == 0)
			return false;
		_position = Coordinates(x, y);

		RectangleShape::setPosition(x * _dimensions, y * _dimensions);
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
		return _position;
	}

	void Cursor::setDimensions(float dimensions)
	{
		this->_dimensions = dimensions;
		RectangleShape::setSize(sf::Vector2f(dimensions, dimensions));
	}

	Cursor* Cursor::spawnChild()
	{
		if(_child != 0)
			return 0;
		else
		{
			_child = new Cursor();
			_child->setBoard(_board);
			_child->setDimensions(_dimensions);
			_child->setPosition(_position);
			_child->setFillColor(_maincolor);
			this->setFillColor(_subcolor);
		}
		return _child;
	}

	Cursor* Cursor::getChild() const
	{
		return _child;
	}

	void Cursor::despawnChild()
	{
		if(_child != 0)
		{
			delete _child;
			_child = 0;
			this->setFillColor(_maincolor);
		}
	}

	void Cursor::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw((sf::RectangleShape)*this, states);
		if(getChild() != 0)
			target.draw(*getChild(), states);
	}
}
