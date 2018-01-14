#include "eventsystem/sfeventsource.hpp"

#include <SFML/Window/Event.hpp>

#include "eventsystem/inputevents.hpp"

namespace qrw
{

SfEventSource::SfEventSource(sf::RenderWindow& window)
	: m_window(window)
{
	keyMap_[sf::Keyboard::Escape]    = KeyboardKey::Esc;
	keyMap_[sf::Keyboard::BackSpace] = KeyboardKey::Backspace;
	keyMap_[sf::Keyboard::Return]    = KeyboardKey::Return;

	keyMap_[sf::Keyboard::W] = KeyboardKey::W;
	keyMap_[sf::Keyboard::A] = KeyboardKey::A;
	keyMap_[sf::Keyboard::S] = KeyboardKey::S;
	keyMap_[sf::Keyboard::D] = KeyboardKey::D;

	keyMap_[sf::Keyboard::Left]  = KeyboardKey::Left;
	keyMap_[sf::Keyboard::Right] = KeyboardKey::Right;
	keyMap_[sf::Keyboard::Up]    = KeyboardKey::Up;
	keyMap_[sf::Keyboard::Down]  = KeyboardKey::Down;
}

const IEvent* SfEventSource::pollEvent()
{
	sf::Event event;
	if(!m_window.pollEvent(event))
	{
		return nullptr;
	}

	// Convert event
	if(event.type == sf::Event::MouseButtonPressed)
	{
		if(event.mouseButton.button == sf::Mouse::Button::Left)
			return new LeftMouseButtonPressedEvent();
		if(event.mouseButton.button == sf::Mouse::Button::Right)
			return new RightMouseButtonPressedEvent();
	}

	else if(event.type == sf::Event::MouseButtonReleased)
	{
		if(event.mouseButton.button == sf::Mouse::Button::Left)
			return new LeftMouseButtonReleasedEvent();
		if(event.mouseButton.button == sf::Mouse::Button::Right)
			return new RightMouseButtonReleasedEvent();
	}

	else if(event.type == sf::Event::MouseMoved)
	{
		sf::Vector2i screenCoordinates(event.mouseMove.x, event.mouseMove.y);
		sf::Vector2f worldCoordinates = m_window.mapPixelToCoords(screenCoordinates);

		return new MouseMovedEvent(screenCoordinates, {(int)worldCoordinates.x, (int)worldCoordinates.y});
	}

	else if(event.type == sf::Event::KeyPressed)
	{
		auto iter = keyMap_.find(event.key.code);
		if(iter != keyMap_.end())
			return new KeyPressedEvent(iter->second);
	}

	else if(event.type == sf::Event::KeyReleased)
	{
		auto iter = keyMap_.find(event.key.code);
		if(iter != keyMap_.end())
			return new KeyReleasedEvent(iter->second);
	}

	else if(event.type == sf::Event::TextEntered)
	{
		// Only handle ascii characters
		if(event.text.unicode < 128)
			return new AsciiInputEvent(static_cast<char>(event.text.unicode));
	}

	return nullptr;
}

} // namespace qrw
