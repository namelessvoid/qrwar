#ifndef QRW_INPUTEVENTS_HPP
#define QRW_INPUTEVENTS_HPP

#include <SFML/System/Vector2.hpp>

#include "eventsystem/event.hpp"

namespace qrw
{

enum class KeyboardKey
{
	Esc,
	Backspace,
	Return,
	A, D, S, W,
	Left, Right, Up, Down
};

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

struct AsciiInputEvent : EventBase<AsciiInputEvent>
{
	AsciiInputEvent(char character)
		: character(character)
	{}

	char character;
};

struct KeyPressedEvent : EventBase<KeyPressedEvent>
{
	KeyPressedEvent(KeyboardKey key)
		: key(key)
	{}

	KeyboardKey key;
};

} // namespace qrw

#endif // QRW_INPUTEVENT_HPP
