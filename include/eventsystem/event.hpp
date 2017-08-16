#ifndef QRW_EVENT_HPP
#define QRW_EVENT_HPP

#include "engine/coordinates.hpp"

namespace qrw
{

struct Event
{
	enum EEventType
	{
		Invalid,
		CursorMoved,
		CursorLeftClicked,
		CursorRightClicked
	};

	Event() :
		type(EEventType::Invalid)
	{}

	Event(EEventType type)
		: type(type)
	{}

	EEventType type;
};

} // namespace qrw

#endif // QRW_EVENT_HPP
