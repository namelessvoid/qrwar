#include "eventsystem/eventsystem.hpp"

#include <cassert>
#include <iostream>

#include <SFML/Window/Event.hpp>

#include "eventsystem/eventhandler.hpp"
#include "eventsystem/inputevents.hpp"

namespace qrw
{

void EventSystem::pushEvent(const Event* event)
{
	m_eventQueue.push(event);
}

void EventSystem::pushSfEvent(const sf::Event &event)
{
	if(event.type == sf::Event::MouseButtonPressed)
	{
		if(event.mouseButton.button == sf::Mouse::Button::Left)
			pushEvent(new LeftMouseButtonClickedEvent());
		else if(event.mouseButton.button == sf::Mouse::Button::Right)
			pushEvent(new RightMouseButtonClickedEvent());
	}
}

void EventSystem::processEventQueue()
{
	const Event* event = nullptr;
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
