#ifndef NAMELESSGUI_RADIOTOGGLEBUTTON_HPP
#define NAMELESSGUI_RADIOTOGGLEBUTTON_HPP value

#include "gui/ng/button.hpp"
#include "gui/ng/buttongroup.hpp"

namespace namelessgui
{
	class RadioToggleButton : public Button
	{
		public:
			RadioToggleButton(sf::RenderWindow* window, ButtonGroup* buttongroup,
				float width, float height,
				std::string text = "",
				const sf::Texture* textureactive = NULL,
				const sf::Texture* textureinainactive = NULL,
				const sf::Texture* texturehover = NULL);
			~RadioToggleButton();

			void draw(sf::RenderTarget& target,
				sf::RenderStates states = sf::RenderStates::Default) const;

		private:
			// Overwritten slots
			void clickedSlot();

			// Button group
			ButtonGroup* buttongroup;
	};
}

#endif
