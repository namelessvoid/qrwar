#include "gui/ng/widgeteventmixin.hpp"

#include "eventsystem/inputevents.hpp"

namespace namelessgui
{

WidgetEventMixin::WidgetEventMixin()
	: leftMouseButtonPressRegistered_(false),
	  rightMouseButtonPressRegistered_(false),
	  mouseFocus_(false),
	  keyboardFocus_(false)
{
}

WidgetEventMixin::~WidgetEventMixin()
{
}

bool WidgetEventMixin::handleEvent(const qrw::IEvent& event)
{
	bool stopEventPropagation = false;

	// A widget that is not visible cannot handle any event
	if(!isVisible())
		return stopEventPropagation;

	// Handle mouse move evets
	if(event.getName() == qrw::MouseMovedEvent::name)
	{
		const qrw::MouseMovedEvent& moveEvent = static_cast<const qrw::MouseMovedEvent&>(event);
		if(!getWidgetArea().contains(moveEvent.screenCoordinates.x, moveEvent.screenCoordinates.y))
		{
			// Mouse focus lost
			if(mouseFocus_)
			{
				mouseFocus_ = false;
				signalMouseFocusLost.emit();
				leftMouseButtonPressRegistered_ = false;
			}
		} // if(!hasMouseFocus)
		else
		{
			// Got mouse focus
			if(!mouseFocus_)
			{
				mouseFocus_ = true;
				signalMouseFocusGained.emit();
			}
			// just moved when already has mouse focus
			else
			{
				signalMouseMoved.emit();
			}
		} // else(hasMouseFocus)
	} // if(MouseMoveEvent)

	if(mouseFocus_)
	{
		if(event.getName() == qrw::LeftMouseButtonPressedEvent::name)
		{
			signalLeftMouseButtonPressed.emit();
			leftMouseButtonPressRegistered_ = true;
			keyboardFocus_ = true;
			stopEventPropagation = true;
		}
		else if(event.getName() == qrw::RightMouseButtonPressedEvent::name)
		{
			rightMouseButtonPressRegistered_ = true;
			stopEventPropagation = true;
		}
		else if(event.getName() == qrw::LeftMouseButtonReleasedEvent::name && leftMouseButtonPressRegistered_)
		{
			signalClicked.emit();
			leftMouseButtonPressRegistered_ = false;
			stopEventPropagation = true;
		}
		else if(event.getName() == qrw::RightMouseButtonReleasedEvent::name && rightMouseButtonPressRegistered_)
		{
			signalRightClicked.emit();
			rightMouseButtonPressRegistered_ = false;
			stopEventPropagation = true;
		}
	}
	else // !mouseFocus
	{
		if(event.getName() == qrw::LeftMouseButtonPressedEvent::name)
		{
			keyboardFocus_ = false;
			signalKeyboardFocusLost.emit();
		}
	}

	return stopEventPropagation;
}

} // namespace namelessgui
