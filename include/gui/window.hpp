#ifndef QRW_WINDOW_HPP
#define QRW_WINDOW_HPP value

#include <vector>

#include <SFML/Graphics/Drawable.hpp>

#include "gui/widget.hpp"

namespace qrw
{
	class Window : public sf::Drawable
	{
		public:
			Window();
			~Window();

			void setVisible(bool visibility = true);
			bool isVisible();

			void addWidget(Widget* widget);

		private:
			bool visible;

			std::vector<Widget*> children;
	};
}
#endif