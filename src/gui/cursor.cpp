#include <iostream>
#include <math.h>

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
	static int counter = 0;

	if(event.getName() == MouseMovedEvent::name)
    {
		const MouseMovedEvent& moveEvent = static_cast<const MouseMovedEvent&>(event);

		sf::Vector2f size = m_spriteComponent->getSize();

        Coordinates newBoardPosition(
			floor(moveEvent.worldCoordinates.x / size.x),
			floor(moveEvent.worldCoordinates.y / size.y));

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
				m_boardPosition = {-1, -1};
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
