#include "eventsystem/sfeventsource.hpp"

#include <SFML/Window/Event.hpp>

#include "eventsystem/inputevents.hpp"

namespace qrw
{

SfEventSource::SfEventSource(sf::RenderWindow& window)
	: m_window(window)
{}

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
		if(event.key.code == sf::Keyboard::Escape)
			return new KeyPressedEvent(KeyPressedEvent::Key::Esc);
	}

	return nullptr;
}

} // namespace qrw
