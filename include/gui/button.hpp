#ifndef QRW_BUTTON_HPP
#define QRW_BUTTON_HPP

#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include "gui/signal.hpp"

namespace qrw
{
	class Button : public sf::Sprite
	{
		public:
			enum STATES
			{
				ES_INACTIVE,
				ES_ACTIVE,
				ES_HOVER
			};

			Button(sf::Window* window, std::string text = "",
				const sf::Texture* textureactive = NULL,
				const sf::Texture* textureinainactive = NULL,
				const sf::Texture* texutrehover = NULL);
			~Button();

			void setText(std::string text);
			std::string getText();
			void setState(STATES state);
			STATES getState() const;

			sf::Vector2f getSize() const;
			void setPosition(float x, float y);
			void setPosition(const sf::Vector2f& position);

			void setTextures(const sf::Texture* textureinactive,
				const sf::Texture* textureactive, 
				const sf::Texture* texturehover);

			// void draw(sf::RenderTarget& target,
			// 	sf::RenderStates states = sf::RenderStates::Default) const;
			void handleEvent(const sf::Event& event);
			void updateSprite();

			// Public signals:
			Signal signalclicked;

		protected:
			bool mouseOnButton();
			sf::Text* text;


		private:
			STATES state;
			sf::Window* window;
			sf::Font* defaultfont;

			const sf::Texture* textures[3];
	};
}

#endif