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
			SpriteWidget(sf::Window* window, float width, float height)
				:	Widget(window, width, height),
					sprite()
			{
			}

			void draw(sf::RenderTarget& target, sf::RenderStates states) const
			{
				target.draw(sprite, states);
			}

			sf::FloatRect getGlobalBounds()
			{
				return sprite.getGlobalBounds();
			}

			void setScale(const sf::Vector2f scale)
			{
				sprite.setScale(scale);
			}

			void setScale(float scalex, float scaley)
			{
				sprite.setScale(scalex, scaley);
			}

			void setPosition(float x, float y)
			{
				sprite.setPosition(x, y);
			}

			const sf::Vector2f& getPosition() const
			{
				return sprite.getPosition();
			}

			const sf::Texture* getTexture() const
			{
				return sprite.getTexture();
			}

			void setTexture(const sf::Texture& texture, bool resetRect = false)
			{
				sprite.setTexture(texture, resetRect);
			}

			const sf::Vector2f& getScale() const
			{
				return sprite.getScale();
			}

		private:
			sf::Sprite sprite;
	};
}
#endif