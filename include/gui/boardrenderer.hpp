#ifndef QRW_BOARDRENDERER_HPP
#define QRW_BOARDRENDERER_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "engine/board.hpp"
#include "gui/texturemanager.hpp"

namespace qrw
{
	class BoardRenderer : public sf::Drawable
	{
		public:
			BoardRenderer();
			~BoardRenderer();

			void setBoard(Board* board);

			void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		private:
			void drawTerrain(sf::RenderTarget& target, TERRAINTYPES terraintype,
				sf::Vector2f position, sf::Vector2f scale) const;
			void drawUnit(sf::RenderTarget& target, int playerid, UNITTYPES unittype,
				sf::Vector2f position, sf::Vector2f scale) const;

			Board* board;
			TextureManager& texturemanager;

			sf::Sprite* plainsquare;
			sf::Sprite* terrainsprites[ET_NUMBEROFTERRAINTYPES];
			sf::Sprite* unitsprites[EUT_NUMBEROFUNITTYPES];
	};
}

#endif