#ifndef QRW_INPUTEVENTS_HPP
#define QRW_INPUTEVENTS_HPP

#include <SFML/System/Vector2.hpp>

#include "eventsystem/event.hpp"

namespace qrw
{

struct MouseMovedEvent : Event
{
    sf::Vector2i screenCoordinates;
    sf::Vector2i worldCoordinates;

    MouseMovedEvent(const sf::Vector2i& screenCoordinates, const sf::Vector2i& worldCoordinates)
        : Event("MOUSE_MOVED")
    {
        this->screenCoordinates = screenCoordinates;
        this->worldCoordinates = worldCoordinates;
    }
};

struct LeftMouseButtonPressedEvent : Event
{
	LeftMouseButtonPressedEvent()
		: Event("LEFT_MOUSE_BUTTON_PRESSED")
    {}
};

struct RightMouseButtonPressedEvent : Event
{
	RightMouseButtonPressedEvent()
		: Event("RIGHT_MOUSE_BUTTON_PRESSED")
    {}
};

struct LeftMouseButtonReleasedEvent : Event
{
	LeftMouseButtonReleasedEvent()
		: Event("LEFT_MOUSE_BUTTON_RELEASED")
	{}
};

struct RightMouseButtonReleasedEvent : Event
{
	RightMouseButtonReleasedEvent()
		: Event("RIGHT_MOUSE_BUTTON_RELEASED")
	{}
};

struct KeyPressedEvent : Event
{
	enum class Key
	{
		Esc
	};

	KeyPressedEvent(Key key)
		: Event("KEY_PRESSED"),
		  key(key)
	{}

	Key key;
};

} // namespace qrw

#endif // QRW_INPUTEVENT_HPP
