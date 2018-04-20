#include <iostream>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "gui/cursor.hpp"
#include "gui/scene.hpp"

#include "engine/board.hpp"

#include "eventsystem/eventsystem.hpp"
#include "eventsystem/inputevents.hpp"

#include "foundation/spritecomponent.hpp"

#include "game/events.hpp"

namespace qrw
{

Cursor::Cursor()
	: SquareMarker(),
	  EventHandler()
{}

Cursor::~Cursor()
{
}

bool Cursor::handleEvent(const IEvent& event)
{
	if(event.getName() == MouseMovedEvent::name)
    {
		const MouseMovedEvent& moveEvent = static_cast<const MouseMovedEvent&>(event);

        sf::Vector2f newPosition;
		sf::Vector2f size = m_spriteComponent->getSize();

		newPosition.x = moveEvent.worldCoordinates.x - (moveEvent.worldCoordinates.x % (int)size.x);
		newPosition.y = moveEvent.worldCoordinates.y - (moveEvent.worldCoordinates.y % (int)size.y);

        Coordinates newBoardPosition((int)newPosition.x / size.x, (int)newPosition.y / size.y);

		if(newBoardPosition != m_boardPosition)
        {
			Board* board = g_scene.getSingleGameObject<Board>();
			if(board->isOnBoard(newBoardPosition))
            {
				setBoardPosition(newBoardPosition);
				 setVisible(true);
            }
            else
            {
				setVisible(false);
            }

			CursorMovedEvent* event = new CursorMovedEvent(m_boardPosition);
			g_eventSystem.pushEvent(event);
        }
    }
	else if(isVisible())
	{
		if(event.getName() == LeftMouseButtonPressedEvent::name)
			g_eventSystem.pushEvent(new CursorLeftClickedEvent(m_boardPosition));
		else if(event.getName() == RightMouseButtonPressedEvent::name)
			g_eventSystem.pushEvent(new CursorRightClickedEvent(m_boardPosition));
	}

	return false;
}

} // namespace qrwar
