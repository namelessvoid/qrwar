#ifndef NAMELESSGUI_WIDGET_HPP
#define NAMELESSGUI_WIDGET_HPP

#include <vector>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "gui/ng/signal.hpp"

namespace namelessgui
{
class Widget
{
	public:
		enum EWidgetStates
		{
			EWS_INACTIVE,
			EWS_ACTIVE,
			EWS_HOVER,
			EWS_COUNT
		};

			Widget();
			virtual ~Widget();

			void setParent(const Widget* parent);

			void addWidget(Widget* widget);

            void handleEvent(const sf::Event& event);

            void setVisible(bool visibility = true);
			bool isVisible();

			void setState(EWidgetStates _state);
			EWidgetStates getState() const;

            void disconnectAllSignals();

            virtual sf::FloatRect getGlobalBounds() = 0;

			virtual void setSize(const sf::Vector2f& size) = 0;
			virtual sf::Vector2f getSize() const = 0;

			virtual sf::Vector2f getPosition() const = 0;
			virtual void setPosition(const sf::Vector2f& position) = 0;

			void setParentAnchor(const sf::Vector2f& anchor);
			void setAnchor(const sf::Vector2f& anchor);

			void setRelativePosition(const sf::Vector2f& relativePosition);

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
			EWidgetStates _state;

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

			sf::Vector2f _parentAnchor;

			sf::Vector2f _anchor;
    };
}
#endif
