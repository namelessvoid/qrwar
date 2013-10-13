#ifndef QRW_RADIOTOGGLEBUTTON_HPP
#define QRW_RADIOTOGGLEBUTTON_HPP value

#include "gui/button.hpp"
#include "gui/buttongroup.hpp"

namespace qrw
{
	class RadioToggleButton : public Button
	{
		public:
			RadioToggleButton(sf::Window* window, ButtonGroup* buttongroup,
				std::string text = "",
				const sf::Texture* textureactive = NULL,
				const sf::Texture* textureinainactive = NULL,
				const sf::Texture* texturehover = NULL);
			~RadioToggleButton();

			void handleEvent(const sf::Event& event);
			void renderOn(sf::RenderTarget& target,
				sf::RenderStates states = sf::RenderStates::Default) const;

		private:
			// Button group
			ButtonGroup* buttongroup;
	};
}

#endif
