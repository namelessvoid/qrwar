#ifndef QRW_BOARDRENDERER_HPP
#define QRW_BOARDRENDERER_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "engine/board.hpp"
#include "texturemanager.hpp"

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
			Board* board;
			TextureManager& texturemanager;

			sf::Sprite* plainsquare;
			sf::Sprite* terrainsprites[];
	};
}

#endif