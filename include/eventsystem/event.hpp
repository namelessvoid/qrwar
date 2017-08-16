#ifndef QRW_EVENT_HPP
#define QRW_EVENT_HPP

#include "engine/coordinates.hpp"

#include "core/sid.hpp"

namespace qrw
{

struct Event
{
	Event(const std::string& name)
		: name(name)
	{}

	SID name;
};

} // namespace qrw

#endif // QRW_EVENT_HPP
