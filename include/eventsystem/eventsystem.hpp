#ifndef QRW_EVENTSYSTEM_HPP
#define QRW_EVENTSYSTEM_HPP

#include <queue>

#include "eventsystem/event.hpp"

namespace qrw
{

class EventSystem
{
public:
	void pushEvent(const Event& event);

	bool popEvent(Event& outEvent);

private:
	std::queue<Event> m_eventQueue;
};

extern EventSystem g_eventSystem;

} // namespace qrw

#endif // QRW_EVENTSYSTEM_HPP
