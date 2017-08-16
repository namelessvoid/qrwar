#ifndef QRW_EVENTS_HPP
#define QRW_EVENTS_HPP

#include "eventsystem/event.hpp"

namespace qrw
{

struct CoordinateEvent : Event
{
    CoordinateEvent(const std::string& name, const Coordinates& coordinates)
        : Event(name)
    {
        this->coordinates = coordinates;
    }

    Coordinates coordinates;
};

struct CursorMovedEvent : CoordinateEvent
{
    CursorMovedEvent(const Coordinates& coordinates)
        : CoordinateEvent("CURSOR_MOVED", coordinates)
    {}
};

struct CursorLeftClickedEvent : CoordinateEvent
{
    CursorLeftClickedEvent(const Coordinates& coordinates)
        : CoordinateEvent("CURSOR_LEFT_CLICKED", coordinates)
    {}
};

struct CursorRightClickedEvent : CoordinateEvent
{
    CursorRightClickedEvent(const Coordinates& coordinates)
        : CoordinateEvent("CURSOR_RIGHT_CLICKED", coordinates)
    {}
};

} // namespace qrw

#endif // QRW_EVENTS_HPP
