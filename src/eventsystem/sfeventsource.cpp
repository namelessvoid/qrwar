#include "eventsystem/sfeventsource.hpp"

#include <SFML/Window/Event.hpp>

#include "eventsystem/inputevents.hpp"

namespace qrw
{

SfEventSource::SfEventSource(sf::RenderWindow& window)
	: m_window(window)
{
	keyMap_[sf::Keyboard::Escape]    = KeyPressedEvent::Key::Esc;
	keyMap_[sf::Keyboard::BackSpace] = KeyPressedEvent::Key::Backspace;
	keyMap_[sf::Keyboard::Return]    = KeyPressedEvent::Key::Return;

	keyMap_[sf::Keyboard::W] = KeyPressedEvent::Key::W;
	keyMap_[sf::Keyboard::A] = KeyPressedEvent::Key::A;
	keyMap_[sf::Keyboard::S] = KeyPressedEvent::Key::S;
	keyMap_[sf::Keyboard::D] = KeyPressedEvent::Key::D;

	keyMap_[sf::Keyboard::Left]  = KeyPressedEvent::Key::Left;
	keyMap_[sf::Keyboard::Right] = KeyPressedEvent::Key::Right;
	keyMap_[sf::Keyboard::Up]    = KeyPressedEvent::Key::Up;
	keyMap_[sf::Keyboard::Down]  = KeyPressedEvent::Key::Down;
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

	if(event.type == sf::Event::MouseButtonReleased)
	{
		if(event.mouseButton.button == sf::Mouse::Button::Left)
			return new LeftMouseButtonReleasedEvent();
		if(event.mouseButton.button == sf::Mouse::Button::Right)
			return new RightMouseButtonReleasedEvent();
	}

	if(event.type == sf::Event::MouseMoved)
	{
		sf::Vector2i screenCoordinates(event.mouseMove.x, event.mouseMove.y);
		sf::Vector2f worldCoordinates = m_window.mapPixelToCoords(screenCoordinates);

		return new MouseMovedEvent(screenCoordinates, {(int)worldCoordinates.x, (int)worldCoordinates.y});
	}

	if(event.type == sf::Event::KeyPressed)
	{
		auto iter = keyMap_.find(event.key.code);
		if(iter != keyMap_.end())
			return new KeyPressedEvent(iter->second);
	}

	if(event.type == sf::Event::TextEntered)
	{
		// Only handle ascii characters
		if(event.text.unicode < 128)
			return new AsciiInputEvent(static_cast<char>(event.text.unicode));
	}

	return nullptr;
}

} // namespace qrw
