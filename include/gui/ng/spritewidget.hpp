#ifndef NAMELESSGUI_SPRITEWIDGET_HPP
#define NAMELESSGUI_SPRITEWIDGET_HPP

#include <memory>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "gui/ng/widget.hpp"

namespace namelessgui
{
	class SpriteWidget : public Widget
	{
		public:
			SpriteWidget(sf::Window* window, float width, float height);

			void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			sf::FloatRect getGlobalBounds();

			void setScale(const sf::Vector2f scale);

			void setScale(float scalex, float scaley);

			void setPosition(float x, float y);

			const sf::Vector2f& getPosition() const;

			const sf::Texture* getTexture() const;

			void setTexture(const sf::Texture& texture, bool resetRect = false);

			const sf::Vector2f& getScale() const;

		private:
			sf::Sprite sprite;
	};
}
#endif