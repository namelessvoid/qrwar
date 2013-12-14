#ifndef NAMELESSGUI_SPRITEWIDGET_HPP
#define NAMELESSGUI_SPRITEWIDGET_HPP

#include <memory>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "gui/ng/widget.hpp"

namespace namelessgui
{
	class SpriteWidget : public Widget, public sf::Sprite
	{
		public:
			SpriteWidget(sf::Window* window, float width, float height)
				:	Widget(window, width, height)
			{
			}

			void draw(sf::RenderTarget& target, sf::RenderStates states) const
			{
				target.draw(static_cast<sf::Sprite>(*this), states);
			}

			sf::FloatRect getGlobalBounds()
			{
				return static_cast<sf::Sprite*>(this)->getGlobalBounds();
			}
	};
}
#endif