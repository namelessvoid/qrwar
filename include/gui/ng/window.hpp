#ifndef NAMELESSGUI_WINDOW_HPP
#define NAMELESSGUI_WINDOW_HPP value

#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>

#include "gui/ng/widget.hpp"

namespace namelessgui
{
	class Window : public sf::RectangleShape
	{
		public:
			Window();
			~Window();

			void setVisible(bool visibility = true);
			bool isVisible() const;

			void addWidget(Widget* widget);

			void draw(sf::RenderTarget&, sf::RenderStates = sf::RenderStates::Default) const;
			void handleEvent(const sf::Event& event);

		private:
			bool _visible;

			std::vector<Widget*> _children;
	};
}
#endif
