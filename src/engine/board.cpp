#include <stdio.h>

#include "engine/board.hpp"
#include "engine/square.hpp"
#include "engine/pathfinding/astar.hpp"

namespace qrw
{
	Board::Board(int width, int height)
	:	_width(width),
	  _height(height)
	{
		int arraysize = height * width;
		_squares = new Square*[arraysize];

		for(int i = 0; i < width; ++i)
			for(int j = 0; j < height; ++j)
				_squares[j * width + i] = new Square(i, j);
		// squares = new Square[arraysize];
		// printf("Array size (height*widht): %i\n", arraysize);
		// printf("array pointer: %i", squares);
		// for(int i = 0; i < arraysize; ++i)
		// {
		// 	squares[i] = new Square();
		// 	printf("current i: %i", i);
		// 	printf(" with pointer: %i\n", squares[i]);
		// }

		// Initialize pathfinding
		_pathfinder = new AStar;
		_pathfinder->setBoard(this);
	}

	Board::~Board()
	{
		for(int i = 0; i < _height*_width; ++i)
			delete _squares[i];
		// delete[] squares;
		delete _pathfinder;
	}

	/*
	 * Returns 0 if indexes are out of range.
	 */
	Square* Board::getSquare(int x, int y)
	{
		if(x < 0 || x >= _width)
			return 0;
		if(y < 0 || y >= _height)
			return 0;
		return _squares[x+y*_width];
	}

	Square* Board::getSquare(sf::Vector2i pos)
	{
		return getSquare(pos.x, pos.y);
	}

	Square* Board::getSquare(const Coordinates& coordinates)
	{
		return getSquare(coordinates.getX(), coordinates.getY());
	}

	int Board::getWidth()
	{
		return _width;
	}

	int Board::getHeight()
	{
		return _height;
	}

	Path* Board::findPath(const Coordinates &start, const Coordinates &end)
	{
		return _pathfinder->findPath(start, end);
	}
}
