#ifndef QRW_EVENTSYSTEM_HPP
#define QRW_EVENTSYSTEM_HPP

#include <queue>
#include <memory>

#include "eventsystem/event.hpp"

namespace qrw
{

class EventSystem
{
public:
	void pushEvent(const Event* event);

	bool popEvent(std::shared_ptr<const Event> &eventOut);

private:
	std::queue<const Event*> m_eventQueue;
};

extern EventSystem g_eventSystem;

} // namespace qrw

#endif // QRW_EVENTSYSTEM_HPP
