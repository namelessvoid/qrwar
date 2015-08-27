#ifndef NAMELESSGUI_WIDGET_HPP
#define NAMELESSGUI_WIDGET_HPP

#include <vector>

#include <SFML/Window/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "gui/ng/signal.hpp"

namespace sf
{
class RenderWindow;
}

namespace namelessgui
{
	class Widget
    {
        public:
			Widget(const Widget* parent = nullptr);
			virtual ~Widget();

			void addWidget(Widget* widget);

            void handleEvent(const sf::Event& event);

            void setVisible(bool visibility = true);
			bool isVisible();

            void disconnectAllSignals();

            virtual sf::FloatRect getGlobalBounds() = 0;

			virtual void setSize(const sf::Vector2f& size) = 0;

			virtual void render(sf::RenderTarget&, sf::RenderStates = sf::RenderStates::Default) const;

            // Signals
			Signal<> signalclicked;
			Signal<> signalrightclicked;
			Signal<> signalmouseentered;
			Signal<> signalmouseleft;
			Signal<> signalmousemoved;
			Signal<> signalleftmousebuttonpressed;
			Signal<const sf::Event&> signalkeypressed;

        protected:
			const Widget* _parent;
			bool _visible;
			std::vector<Widget*> _children;

        private:
            /**
             * @brief Registeres when left mouse button is pressed.
             *
             * Is set to true if the left mouse button was pressed while mouse cursor was on the widget. If the mouse
             * is released again while on the widget a click event took place. Reset leftMouseButtonpressRegistered if
             * mouse leaves focus.
             */
			bool _leftMouseButtonPressRegistered;

            /**
             * @brief Registeres when right mouse button is pressed.
             *
             * Is set to true if the right mouse button was pressed while mouse cursor was on the widget. If the mouse
             * is released again while on the widget a click event took place. Reset leftMouseButtonpressRegistered if
             * mouse leaves focus.
             */
			bool _rightMouseButtonPressRegistered;

            /**
             * @brief Saves the last known mouse focus state.
             *
             * Is used to determine if a signalmouseleft or signalmouseentered signal has to be emitted. It holds the last
             * known mouse focus state which means that in case of mouseFocus followed by hasMouseFocus() == true the mouse
             * cursor entered the widget or other way round left the widget.
             */
			bool _mouseFocus;
    };
}
#endif
