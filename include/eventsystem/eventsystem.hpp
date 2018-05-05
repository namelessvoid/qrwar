#ifndef QRW_EVENTSYSTEM_HPP
#define QRW_EVENTSYSTEM_HPP

#include <queue>
#include <set>
#include <map>
#include <cassert>

#include "core/prioritylist.hpp"

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

	void update(float elapsedTimeInSeconds);

	void registerEventHandler(EventHandler* eventHandler);

	void deregisterEventHandler(EventHandler* eventHandler);

private:
	void propagateEventToHandlers(const IEvent* event);
	
	void updateButtonStates(const IEvent* event);

	void emitMouseButtonHeldEvent(float elapsedTimeInSeconds);

	std::queue<const IEvent*> m_eventQueue;

	PriorityList<EventHandler*> handlers_;

	SystemEventSource* m_systemEventSource;

	bool leftMouseButtonDown_;
	float LEFT_MOUSE_BUTTON_HELD_TIMEOUT = 0.5;
	float leftMouseButtonCurrentlyHeld_;
};

extern EventSystem g_eventSystem;

} // namespace qrw

#endif // QRW_EVENTSYSTEM_HPP
