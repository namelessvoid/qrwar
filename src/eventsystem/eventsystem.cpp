#include "eventsystem/eventsystem.hpp"

#include <cassert>
#include <iostream>

#include <SFML/Window/Event.hpp>

#include "eventsystem/eventhandler.hpp"
#include "eventsystem/inputevents.hpp"

namespace qrw
{

void EventSystem::startUp(SystemEventSource *systemEventSource)
{
	assert(systemEventSource!=nullptr);
	m_systemEventSource = systemEventSource;
}

void EventSystem::shutDown()
{
	assert(m_systemEventSource!=nullptr);
	delete m_systemEventSource;

	while(m_eventQueue.size() > 0)
	{
		delete m_eventQueue.front();
		m_eventQueue.pop();
	}
}

void EventSystem::pushEvent(const Event* event)
{
	m_eventQueue.push(event);
}

void EventSystem::processEvents()
{
	const Event* event = nullptr;

	while((event = m_systemEventSource->pollEvent()) != nullptr)
	{
		pushEvent(event);
	}

	while(m_eventQueue.size() > 0)
	{
		event = m_eventQueue.front();
		m_eventQueue.pop();

		for(auto handler : m_eventHandlers)
		{
			handler->handleEvent(*event);
		}

		delete event;
	}
}

void EventSystem::registerEventHandler(EventHandler* eventHandler)
{
	assert(eventHandler!=nullptr);
	assert(m_eventHandlers.find(eventHandler)==m_eventHandlers.end());
	m_eventHandlers.insert(eventHandler);

	std::cout << "Registered event handler. Total count: " << m_eventHandlers.size() << std::endl << std::flush;
}

void EventSystem::deregisterEventHandler(EventHandler* eventHandler)
{
	assert(eventHandler!=nullptr);
	assert(m_eventHandlers.find(eventHandler)!=m_eventHandlers.end());
	m_eventHandlers.erase(eventHandler);
}

} // namespace qrw
