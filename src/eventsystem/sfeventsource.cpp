#include "eventsystem/sfeventsource.hpp"

#include <SFML/Window/Event.hpp>

#include "eventsystem/inputevents.hpp"

namespace qrw
{

SfEventSource::SfEventSource(sf::RenderWindow& window)
	: m_window(window)
{}

const Event* SfEventSource::pollEvent()
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
			return new LeftMouseButtonClickedEvent();
		else if(event.mouseButton.button == sf::Mouse::Button::Right)
			return new RightMouseButtonClickedEvent();
	}

	if(event.type == sf::Event::MouseMoved)
	{
		sf::Vector2i screenCoordinates(event.mouseMove.x, event.mouseMove.y);
		sf::Vector2f worldCoordinates = m_window.mapPixelToCoords(screenCoordinates);

		return new MouseMovedEvent(screenCoordinates, {(int)worldCoordinates.x, (int)worldCoordinates.y});
	}

	return nullptr;
}

} // namespace qrw
