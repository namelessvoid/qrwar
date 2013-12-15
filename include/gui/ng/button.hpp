#ifndef NAMELESSGUI_BUTTON_HPP
#define NAMELESSGUI_BUTTON_HPP

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include "gui/ng/spritewidget.hpp"

namespace namelessgui
{
	class Button : public SpriteWidget
	{
		public:
			enum STATES
			{
				ES_INACTIVE,
				ES_ACTIVE,
				ES_HOVER
			};

			Button(sf::Window* window, float width, float height, std::string text = "",
				const sf::Texture* textureactive = NULL,
				const sf::Texture* textureinainactive = NULL,
				const sf::Texture* texutrehover = NULL);
			~Button();

			void setText(std::string text);
			std::string getText();
			void setState(STATES state);
			STATES getState() const;

			void setPosition(float x, float y);
			void setPosition(const sf::Vector2f& position);

			void setTextures(const sf::Texture* textureinactive,
				const sf::Texture* textureactive,
				const sf::Texture* texturehover);

			// void draw(sf::RenderTarget& target,
			// 	sf::RenderStates states = sf::RenderStates::Default) const;
			void updateSprite();

		protected:
			sf::Text* text;


		private:
			// Slots
			void leftMousebuttonPressedSlot();
			void mouseEnteredSlot();
			void clickedSlot();
			void mouseLeftSlot();

			STATES state;
			sf::Font* defaultfont;

			const sf::Texture* textures[3];
	};
}

#endif
