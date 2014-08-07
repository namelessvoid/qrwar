#include <stdio.h>

#include "engine/board.hpp"
#include "engine/pathfinding/astar.hpp"

namespace qrw
{
	Board::Board(int width, int height)
	:	height(height),
		width(width)
	{
		int arraysize = height * width;
		squares = new Square*[arraysize];

		for(int i = 0; i < width; ++i)
			for(int j = 0; j < height; ++j)
				squares[j * width + i] = new Square(i, j);
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
		pathfinder = new AStar;
		pathfinder->setBoard(this);
	}

	Board::~Board()
	{
		for(int i = 0; i < height*width; ++i)
			delete squares[i];
		// delete[] squares;
		delete pathfinder;
	}

	/*
	 * Returns 0 if indexes are out of range.
	 */
	Square* Board::getSquare(int x, int y)
	{
		if(x < 0 || x >= width)
			return 0;
		if(y < 0 || y >= height)
			return 0;
		return squares[x+y*width];
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
		return width;
	}

	int Board::getHeight()
	{
		return height;
	}

	Path* Board::findPath(const Coordinates &start, const Coordinates &end)
	{
		return pathfinder->findPath(start, end);
	}
}
