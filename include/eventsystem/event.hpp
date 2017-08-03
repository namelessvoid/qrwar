#ifndef QRW_EVENT_HPP
#define QRW_EVENT_HPP

#include "engine/coordinates.hpp"

namespace qrw
{

class Event
{
public:
	enum EEventType
	{
		Invalid,
		CursorMoved,
		CursorLeftClicked,
		CursorRightClicked
	};

	Event()
		: type(EEventType::Invalid)
	{
	}

	Event(EEventType type, const Coordinates& coordinates)
		: type(type),
		  coordinates(coordinates)
	{
	}

	Event(const Event& rhs)
		: type(rhs.type),
		  coordinates(rhs.coordinates)
	{
	}

	Event& operator=(const Event& rhs)
	{
		type = rhs.type;
		coordinates = rhs.coordinates;
		return *this;
	}

	EEventType type;

	Coordinates coordinates;
};

} // namespace qrw

#endif // QRW_EVENT_HPP
