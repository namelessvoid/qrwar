#ifndef QRW_BOARD_HPP
#define QRW_BOARD_HPP

#include <memory>
#include <map>

#include <SFML/System/Vector2.hpp>

namespace qrw
{
	class AbstractPathfinder;
	class Path;
	class Coordinates;
	class Square;
	class Unit;

	class Board
	{
		public:
			typedef std::shared_ptr<Board> Ptr;

			Board(int width, int height);
			~Board();

			Square* getSquare(int x, int y);
			Square* getSquare(sf::Vector2i pos);
			Square* getSquare(const Coordinates& coordinates);

			void setUnit(const Coordinates& position, std::shared_ptr<Unit>& unit);
			void removeUnit(const Coordinates& position);
			void moveUnit(const Coordinates& source, const Coordinates& destination);
			bool isUnitAt(const Coordinates& position);
			std::shared_ptr<Unit> getUnit(const Coordinates& position);
			const std::map<Coordinates, std::shared_ptr<Unit>>& getUnits() const;

			int getWidth();
			int getHeight();

			bool isOnBoard(Coordinates coordinates);

			bool isAccessible(const Coordinates& coordinates);

			/**
			 * @brief Call pathfinding algorithm to find path from start to end.
			 * @param start Coordinates of the start.
			 * @param end Coordinates of the end.
			 * @return Pointer to found path or nullptr if no path could be found.
			 */
			Path* findPath(const Coordinates& start, const Coordinates& end);

		private:
			Square** _squares;

			std::map<Coordinates, std::shared_ptr<Unit>> _units;

			int _width;
			int _height;

			AbstractPathfinder* _pathfinder;
	};
}

#endif
