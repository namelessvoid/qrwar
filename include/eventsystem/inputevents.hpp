#ifndef QRW_INPUTEVENTS_HPP
#define QRW_INPUTEVENTS_HPP

#include <SFML/System/Vector2.hpp>

#include "eventsystem/event.hpp"

namespace qrw
{

struct MouseMovedEvent : EventBase<MouseMovedEvent>
{
    sf::Vector2i screenCoordinates;
    sf::Vector2i worldCoordinates;

    MouseMovedEvent(const sf::Vector2i& screenCoordinates, const sf::Vector2i& worldCoordinates)
    {
        this->screenCoordinates = screenCoordinates;
        this->worldCoordinates = worldCoordinates;
    }
};

struct LeftMouseButtonPressedEvent : EventBase<LeftMouseButtonPressedEvent>
{
};

struct RightMouseButtonPressedEvent : EventBase<RightMouseButtonPressedEvent>
{
};

struct LeftMouseButtonReleasedEvent : EventBase<LeftMouseButtonReleasedEvent>
{
};

struct RightMouseButtonReleasedEvent : EventBase<RightMouseButtonReleasedEvent>
{
};

struct KeyPressedEvent : EventBase<KeyPressedEvent>
{
	enum class Key
	{
		Esc
	};

	KeyPressedEvent(Key key)
		: key(key)
	{}

	Key key;
};

} // namespace qrw

#endif // QRW_INPUTEVENT_HPP
