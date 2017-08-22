#ifndef QRW_INPUTEVENTS_HPP
#define QRW_INPUTEVENTS_HPP

#include <SFML/System/Vector2.hpp>

#include "eventsystem/event.hpp"

namespace qrw
{

struct MouseMovedEvent : Event
{
    sf::Vector2i screenCoordinates;
    sf::Vector2i worldCoordinates;

    MouseMovedEvent(const sf::Vector2i& screenCoordinates, const sf::Vector2i& worldCoordinates)
        : Event("MOUSE_MOVED")
    {
        this->screenCoordinates = screenCoordinates;
        this->worldCoordinates = worldCoordinates;
    }
};

struct LeftMouseButtonClickedEvent : Event
{
    LeftMouseButtonClickedEvent()
        : Event("LEFT_MOUSE_BUTTON_CLICKED")
    {}
};

struct RightMouseButtonClickedEvent : Event
{
    RightMouseButtonClickedEvent()
        : Event("RIGHT_MOUSE_BUTTON_CLICKED")
    {}
};

} // namespace qrw

#endif // QRW_INPUTEVENT_HPP
