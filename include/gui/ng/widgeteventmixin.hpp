#ifndef NAMELESSGUI_WIDGETEVENTMIXIN_HPP
#define NAMELESSGUI_WIDGETEVENTMIXIN_HPP

#include <SFML/Graphics/Rect.hpp>

#include "signal.hpp"

#include "eventsystem/eventhandler.hpp"

namespace namelessgui {

class WidgetEventMixin
{
public:
    WidgetEventMixin();

    ~WidgetEventMixin();

    virtual bool handleEvent(const qrw::IEvent& event);

    virtual bool isVisible() const = 0;

    /**
     * @brief Get the area of the widget.
     *
     * Get a rectangle defining in which area the widget will
     * respond to mouse events (hover, clicks, ...).
     *
     * @return The area defined as a rectangle.
     */
    virtual sf::FloatRect getWidgetArea() const = 0;

    bool hasMouseFocus() const { return mouseFocus_; }
    bool hasKeyboardFocus() const { return keyboardFocus_; }

    // Signals
    Signal<> signalClicked;
    Signal<> signalMouseFocusGained;
    Signal<> signalMouseFocusLost;
    Signal<> signalLeftMouseButtonPressed;
    Signal<float> signalLeftMouseButtonHeld;
    Signal<> signalKeyboardFocusLost;

protected:
    inline void setKeyboardFocus(bool focus) { keyboardFocus_ = focus; }

private:
    WidgetEventMixin(const WidgetEventMixin& rhs) = delete;

    WidgetEventMixin& operator=(const WidgetEventMixin& rhs) = delete;

    /**
     * @brief Registeres when left mouse button is pressed.
     *
     * Is set to true if the left mouse button was pressed while mouse cursor was on the widget. If the mouse
     * is released again while on the widget a click event took place. Reset leftMouseButtonpressRegistered if
     * mouse leaves focus.
     */
    bool leftMouseButtonPressRegistered_;

    /**
     * @brief Saves the last known mouse focus state.
     *
     * Is used to determine if a signalmouseleft or signalmouseentered signal has to be emitted. It holds the last
     * known mouse focus state which means that in case of mouseFocus followed by hasMouseFocus() == true the mouse
     * cursor entered the widget or other way round left the widget.
     */
    bool mouseFocus_;

    bool keyboardFocus_;
};


} // namespace namelessgui

#endif // NAMELESSGUI_WIDGETEVENTMIXIN_HPP
