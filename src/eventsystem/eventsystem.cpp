#include "eventsystem/eventsystem.hpp"

#include <iostream>

namespace qrw
{

void EventSystem::pushEvent(const Event& event)
{
	m_eventQueue.push(event);
}

bool EventSystem::popEvent(Event& outEvent)
{
	if(m_eventQueue.size() == 0)
		return false;

	outEvent = m_eventQueue.front();
	m_eventQueue.pop();
	return true;
}

} // namespace qrw
