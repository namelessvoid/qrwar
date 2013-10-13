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

        protected:
            bool hasMouseFocus();

        private:
            bool mouseFocus;
            const sf::Window* window;
    };
}
#endif
