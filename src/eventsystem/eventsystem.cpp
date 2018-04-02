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

	leftMouseButtonDown_ = false;
	leftMouseButtonCurrentlyHeld_ = 0;
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

void EventSystem::pushEvent(const IEvent* event)
{
	m_eventQueue.push(event);
}

void EventSystem::update(float elapsedTimeInSeconds)
{
	const IEvent* event = nullptr;

	while((event = m_systemEventSource->pollEvent()) != nullptr)
	{
		pushEvent(event);
	}

	while(m_eventQueue.size() > 0)
	{
		event = m_eventQueue.front();
		m_eventQueue.pop();

		updateButtonStates(event);
		propagateEventToHandlers(event);

		delete event;
	}

	emitMouseButtonHeldEvent(elapsedTimeInSeconds);
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

void EventSystem::propagateEventToHandlers(const IEvent* event)
{
	for(auto handler : m_eventHandlers)
	{
		handler->handleEvent(*event);
	}
}

void EventSystem::updateButtonStates(const IEvent* event)
{
	if(event->getName() == LeftMouseButtonPressedEvent::name)
	{
		leftMouseButtonDown_ = true;
	}
	else if(event->getName() == LeftMouseButtonReleasedEvent::name)
	{
		leftMouseButtonDown_ = false;
	}
}

void EventSystem::emitMouseButtonHeldEvent(float elapsedTimeInSeconds)
{
	if(leftMouseButtonDown_)
	{
		if(leftMouseButtonCurrentlyHeld_ >= LEFT_MOUSE_BUTTON_HELD_TIMEOUT)
		{
			IEvent* event = new LeftMouseButtonHeldEvent(elapsedTimeInSeconds);
			propagateEventToHandlers(event);
			delete event;
		}
		else
		{
			leftMouseButtonCurrentlyHeld_ += elapsedTimeInSeconds;
		}
	}
	else
	{
		leftMouseButtonCurrentlyHeld_ = 0;
	}
}

} // namespace qrw
