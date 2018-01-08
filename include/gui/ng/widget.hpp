#ifndef NAMELESSGUI_WIDGET_HPP
#define NAMELESSGUI_WIDGET_HPP

#include <vector>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "gui/ng/signal.hpp"
#include "gui/ng/widgeteventmixin.hpp"

namespace sf
{
class RenderWindow;
}

namespace namelessgui
{
class Widget : public WidgetEventMixin
{
	public:
			/**
			 * @brief Construct a new widget.
			 * @param id The ID assigned to the widget which can be used to identify the widget.
			 *           Defaults to empty string.
			 */
			Widget(std::string id = "");

			virtual ~Widget();

			/**
			 * @brief Get the ID of the widget (see constructor).
			 * @return The ID of the widget or empty string if none was assigned.
			 */
			const std::string& getId() const;

			void setParent(const Widget* parent);

			void addWidget(Widget* widget);

            void setVisible(bool visibility = true);
			bool isVisible() const;

            void disconnectAllSignals();

			virtual void setSize(const sf::Vector2f& size) = 0;
			virtual sf::Vector2f getSize() const = 0;

			virtual sf::Vector2f getPosition() const = 0;
			virtual void setPosition(const sf::Vector2f& position) = 0;

			void setParentAnchor(const sf::Vector2f& anchor);
			void setAnchor(const sf::Vector2f& anchor);

			void setRelativePosition(const sf::Vector2f& relativePosition);
			void updatePosition();

			virtual void render(sf::RenderTarget&, sf::RenderStates = sf::RenderStates::Default) const;

        protected:
			const Widget* _parent;
			bool _visible;
			std::vector<Widget*> _children;

        private:
			/**
			 * @brief _id Used to identify a widget.
			 */
			std::string _id;

			sf::Vector2f _parentAnchor;

			sf::Vector2f _anchor;

			sf::Vector2f _relativePosition;
    };
}
#endif
