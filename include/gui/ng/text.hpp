#ifndef NAMELESSGUI_TEXT_HPP
#define NAMELESSGUI_TEXT_HPP

#include <string>

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/String.hpp>

#include "gui/ng/widget.hpp"

namespace namelessgui
{
    class Text : public Widget
	{
		public:
            Text();

			virtual void render(sf::RenderTarget& target, sf::RenderStates states) const override;

			sf::FloatRect getWidgetArea();

			void setFont(sf::Font& font);
			const sf::Font* getFont() const { return _text.getFont(); }

			void setColor(const sf::Color& color);

			void setCharacterSize(unsigned int _size);
			unsigned int getCharacterSize() const { return _text.getCharacterSize(); }

			void setText(const std::string& text);
			const std::string& getText() const;

			void setPosition(const sf::Vector2f& position);

			sf::Vector2f getPosition() const override;

			virtual void setSize(const sf::Vector2f&) override {}
			virtual sf::Vector2f getSize() const override;

		private:
			std::string _stdText;
			sf::Text _text;
			sf::Font _font;
	};

} // namespace namelessgui

#endif // NAMELESSGUI_TEXT_HPP
