#ifndef QRW_BOARD_HPP
#define QRW_BOARD_HPP

#include <SFML/System/Vector2.hpp>

#include "engine/square.hpp"
#include "engine/coordinates.hpp"

namespace qrw
{

	class Board
	{
		public:
			Board(int width, int height);
			~Board();

			Square* getSquare(int x, int y);
			Square* getSquare(sf::Vector2i pos);
			Square* getSquare(const Coordinates& coordinates);

			int getWidth();
			int getHeight();

		private:
			Square** squares;

			int width;
			int height;
	};
}

#endif
