#ifndef QRW_EVENT_HPP
#define QRW_EVENT_HPP

#include "engine/coordinates.hpp"

#include "core/sid.hpp"

namespace qrw
{

struct IEvent
{
	virtual ~IEvent()
	{}

	virtual const SID& getName() const = 0;
};

template<class T>
struct EventBase : IEvent
{
	virtual ~EventBase()
	{}

	virtual const SID& getName() const override
	{
		return name;
	}


	static const SID name;
};

} // namespace qrw

#endif // QRW_EVENT_HPP
