#ifndef QRW_EVENTSYSTEM_HPP
#define QRW_EVENTSYSTEM_HPP

#include <queue>
#include <set>
#include <cassert>

#include "eventsystem/event.hpp"
#include "eventsystem/systemeventsource.hpp"

namespace sf
{
class IEvent;
}

namespace qrw
{

class EventHandler;

class EventSystem
{
public:
	void startUp(SystemEventSource* systemEventSource);

	void shutDown();

	void pushEvent(const IEvent* event);

	void update(float elapsedTime);

	void registerEventHandler(EventHandler* eventHandler);

	void deregisterEventHandler(EventHandler* eventHandler);

private:
	std::queue<const IEvent*> m_eventQueue;

	std::set<EventHandler*> m_eventHandlers;

	SystemEventSource* m_systemEventSource;
};

extern EventSystem g_eventSystem;

} // namespace qrw

#endif // QRW_EVENTSYSTEM_HPP
