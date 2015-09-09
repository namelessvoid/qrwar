#ifndef QRW_BOARD_HPP
#define QRW_BOARD_HPP

#include <memory>

#include <SFML/System/Vector2.hpp>

namespace qrw
{
	class AbstractAlgorithm;
	class Path;
	class Coordinates;
	class Square;

	class Board
	{
		public:
			typedef std::shared_ptr<Board> Ptr;

			Board(int width, int height);
			~Board();

			Square* getSquare(int x, int y);
			Square* getSquare(sf::Vector2i pos);
			Square* getSquare(const Coordinates& coordinates);

			int getWidth();
			int getHeight();

			bool isOnBoard(Coordinates coordinates);

			/**
			 * @brief Call pathfinding algorithm to find path from start to end.
			 * @param start Coordinates of the start.
			 * @param end Coordinates of the end.
			 * @return Pointer to found path or nullptr if no path could be found.
			 */
			Path* findPath(const Coordinates& start, const Coordinates& end);

		private:
			Square** _squares;

			int _width;
			int _height;

			AbstractAlgorithm* _pathfinder;
	};
}

#endif
