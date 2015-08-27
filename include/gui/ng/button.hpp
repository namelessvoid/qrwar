#ifndef NAMELESSGUI_BUTTON_HPP
#define NAMELESSGUI_BUTTON_HPP

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "gui/ng/spritewidget.hpp"
#include "gui/ng/label.hpp"

namespace namelessgui
{
	class Button : public RectangularWidget
	{
		public:
			Button(const sf::Texture* textureactive = NULL,
				const sf::Texture* textureinainactive = NULL,
				const sf::Texture* texutrehover = NULL);
			~Button();

			void setText(std::string text);

			void setPosition(float x, float y);
			void setPosition(const sf::Vector2f& position);

			void setTextures(const sf::Texture* textureinactive,
				const sf::Texture* textureactive,
				const sf::Texture* texturehover);

			void updateSprite();

			virtual void render(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

		protected:
			Label* _label;
			RectangularWidget* _image;


		private:
			// Slots
			void leftMousebuttonPressedSlot();
			void mouseEnteredSlot();
			void clickedSlot();
			void mouseLeftSlot();

			EWidgetStates _state;
			sf::Font* _defaultfont;

			const sf::Texture* _textures[3];
	};
}

#endif
