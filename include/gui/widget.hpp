#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "gui/signal.hpp"

namespace qrw
{
    class Widget : public sf::Sprite
    {
        public:
            Widget(sf::Window* window);
            ~Widget();

            void handleEvent(sf::Event& event);

            // Signals
            Signal signalclicked;
            Signal signalmouseentered;
            Signal signalmouseleft;

        protected:
            bool hasMouseFocus();

            sf::Window* window;
    };
}
#endif
