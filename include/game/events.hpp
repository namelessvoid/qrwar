#ifndef QRW_EVENTS_HPP
#define QRW_EVENTS_HPP

#include "eventsystem/event.hpp"

namespace qrw
{

template<class T>
struct CoordinateEvent : EventBase<T>
{
	virtual ~CoordinateEvent()
	{}

	CoordinateEvent(const Coordinates& coordinates)
    {
        this->coordinates = coordinates;
    }

    Coordinates coordinates;
};

struct CursorMovedEvent : CoordinateEvent<CursorMovedEvent>
{
    CursorMovedEvent(const Coordinates& coordinates)
		: CoordinateEvent(coordinates)
    {}
};

struct CursorLeftClickedEvent : CoordinateEvent<CursorLeftClickedEvent>
{
    CursorLeftClickedEvent(const Coordinates& coordinates)
		: CoordinateEvent(coordinates)
    {}
};

struct CursorRightClickedEvent : CoordinateEvent<CursorRightClickedEvent>
{
    CursorRightClickedEvent(const Coordinates& coordinates)
		: CoordinateEvent(coordinates)
    {}
};

} // namespace qrw

#endif // QRW_EVENTS_HPP
