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
			Label();

			virtual void render(sf::RenderTarget& target, sf::RenderStates states) const override;

			sf::FloatRect getGlobalBounds();

			void setFont(sf::Font& font);

			void setColor(const sf::Color& color);

			void setCharacterSize(unsigned int _size);

			void setText(const sf::String& _text);

			void setPosition(const sf::Vector2f& position);

			sf::Vector2f getPosition() const override;

			virtual void setSize(const sf::Vector2f&) override {}
			virtual sf::Vector2f getSize() const override;

		private:
			sf::Text _text;
			sf::Font _font;
	};
}
#endif
