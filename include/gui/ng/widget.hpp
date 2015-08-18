#ifndef NAMELESSGUI_WIDGET_HPP
#define NAMELESSGUI_WIDGET_HPP

#include <SFML/Window/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "gui/ng/signal.hpp"
#include "gui/ng/singleparametersignal.hpp"

namespace sf
{
class RenderWindow;
}

namespace namelessgui
{
    class Widget : public sf::Drawable
    {
        public:
			Widget(sf::RenderWindow* window, float width, float height);
			Widget(sf::RenderWindow* window, sf::Vector2f size);
            ~Widget();

            void handleEvent(const sf::Event& event);

            void setVisible(bool visibility = true);

            void disconnectAllSignals();

			void setSize(sf::Vector2f size);
			sf::Vector2f getSize() const;

            virtual sf::FloatRect getGlobalBounds() = 0;

            // Signals
            Signal signalclicked;
            Signal signalrightclicked;
            Signal signalmouseentered;
            Signal signalmouseleft;
            Signal signalmousemoved;
            Signal signalleftmousebuttonpressed;
            SingleParameterSignal<const sf::Event&> signalkeypressed;

        protected:
            bool hasMouseFocus();
			const sf::RenderWindow* window;
            bool visible;

        private:
            /**
             * @brief Registeres when left mouse button is pressed.
             *
             * Is set to true if the left mouse button was pressed while mouse cursor was on the widget. If the mouse
             * is released again while on the widget a click event took place. Reset leftMouseButtonpressRegistered if
             * mouse leaves focus.
             */
            bool leftMouseButtonPressRegistered;

            /**
             * @brief Registeres when right mouse button is pressed.
             *
             * Is set to true if the right mouse button was pressed while mouse cursor was on the widget. If the mouse
             * is released again while on the widget a click event took place. Reset leftMouseButtonpressRegistered if
             * mouse leaves focus.
             */
            bool rightMouseButtonPressRegistered;

            /**
             * @brief Saves the last known mouse focus state.
             *
             * Is used to determine if a signalmouseleft or signalmouseentered signal has to be emitted. It holds the last
             * known mouse focus state which means that in case of mouseFocus followed by hasMouseFocus() == true the mouse
             * cursor entered the widget or other way round left the widget.
             */
            bool mouseFocus;

            /**
             * Holds size of the widget.
             */
            sf::Vector2f size;
    };
}
#endif
