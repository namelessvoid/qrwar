#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <SFML/Window/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "gui/signal.hpp"

namespace qrw
{
    class Widget : public sf::Sprite
    {
        public:
            Widget(sf::Window* window);
            ~Widget();

            void handleEvent(const sf::Event& event);

            // Signals
            Signal signalclicked;
            Signal signalmouseentered;
            Signal signalmouseleft;
            Signal signalmousemoved;
            Signal signalleftmousebuttonpressed;

        protected:
            bool hasMouseFocus();

        private:
            // Is set to true if the left mouse button was pressed while mouse cursor was on the widget. If the mouse
            // is released again while on the widget a click event took place. Reset leftMouseButtonpressRegistered if
            // mouse leaves focus.
            bool leftMouseButtonPressRegistered;
            bool mouseFocus;
            const sf::Window* window;
    };
}
#endif
