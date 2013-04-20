#ifndef QRW_SQUARESELECTION_HPP
#define QRW_SQUARESELECTION_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "engine/board.hpp"

namespace qrw
{
	class Cursor
	{
		public:
			static Cursor* getCursor();

			~Cursor();

			void setBoard(Board* board);
			sf::Vector2i getPosition();

			/**
			 * Move the cursor or (if available) move child cursor.
			 */
			bool move(int dx, int dy);
			bool setPosition(int x, int y);
			bool setPosition(sf::Vector2i pos);

			Cursor* spawnChild();
			Cursor* getChild();
			void despawnChild();

			/**
			 * @argument position Position on the screen (pixles)
			 * @argument size Size of the cursor on the screen in pixles.
			 */
			void draw(sf::RenderTarget& target, sf::Vector2f position, float size);
			void drawChild(sf::RenderTarget& target, sf::Vector2f position, float size);

		private:
			Cursor();

			static Cursor* cursor;
			// Child cursor
			Cursor* child;

			sf::Vector2i position;
			Board* board;
	};
}

#endif