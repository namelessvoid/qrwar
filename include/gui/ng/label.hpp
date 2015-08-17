#ifndef NAMELESSGUI_LABEL_HPP
#define NAMELESSGUI_LABEL_HPP

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/String.hpp>


#include "gui/ng/widget.hpp"

namespace namelessgui
{
	class Label : public Widget
	{
		public:
			Label(sf::RenderWindow* window, float width = 0, float height = 0);

			void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			sf::FloatRect getGlobalBounds();

			void setFont(sf::Font& font);

			void setColor(const sf::Color& color);

			void setCharacterSize(unsigned int size);

			void setText(const sf::String& text);

			void setPosition(float x, float y);

		private:
			sf::Text text;
	};
}
#endif
