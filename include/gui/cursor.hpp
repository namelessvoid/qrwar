#ifndef QRW_SQUARESELECTION_HPP
#define QRW_SQUARESELECTION_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "engine/coordinates.hpp"

namespace qrw
{
	class Board;

	class Cursor : public sf::RectangleShape
	{
		public:
			static Cursor* getCursor();

			~Cursor();

			void setBoard(Board* _board);

			/**
			 * Move the cursor or (if available) move child cursor.
			 */
			bool move(int dx, int dy);
			bool setPosition(int x, int y);
			bool setPosition(sf::Vector2i pos);
			bool setPosition(Coordinates pos);

			const Coordinates& getPosition() const;

			void setDimensions(float _dimensions);

			Cursor* spawnChild();
			Cursor* getChild() const;
			void despawnChild();

			/**
			 * @argument position Position on the screen (pixles)
			 * @argument size Size of the cursor on the screen in pixles.
			 */
			void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		private:
			Cursor();

			static Cursor* _cursor;
			// Child cursor
			Cursor* _child;

			sf::Color _maincolor;
			sf::Color _subcolor;

			Coordinates _position;
			float _dimensions;
			Board* _board;
	};
}

#endif
