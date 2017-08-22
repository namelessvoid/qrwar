#ifndef QRW_EVENTSYSTEM_HPP
#define QRW_EVENTSYSTEM_HPP

#include <queue>
#include <set>

#include "eventsystem/event.hpp"

namespace sf
{
class Event;
}

namespace qrw
{

class EventHandler;

class EventSystem
{
public:
	void pushEvent(const Event* event);

	void pushSfEvent(const sf::Event& event);

	void processEventQueue();

	void registerEventHandler(EventHandler* eventHandler);

	void deregisterEventHandler(EventHandler* eventHandler);

private:
	std::queue<const Event*> m_eventQueue;

	std::set<EventHandler*> m_eventHandlers;
};

extern EventSystem g_eventSystem;

} // namespace qrw

#endif // QRW_EVENTSYSTEM_HPP
