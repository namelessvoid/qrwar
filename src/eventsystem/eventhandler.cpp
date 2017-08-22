#include "eventsystem/eventhandler.hpp"

#include "eventsystem/eventsystem.hpp"

namespace qrw
{

EventHandler::EventHandler()
{
	g_eventSystem.registerEventHandler(this);
}

EventHandler::~EventHandler()
{
	g_eventSystem.deregisterEventHandler(this);
}

}
