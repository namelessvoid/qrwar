#include <iostream>
#include <math.h>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "game/constants.hpp"
#include "gui/cursor.hpp"
#include "gui/scene.hpp"

#include "engine/board.hpp"

#include "eventsystem/eventsystem.hpp"
#include "eventsystem/inputevents.hpp"

#include "physics/physicsengine.hpp"

#include "foundation/spritecomponent.hpp"

#include "game/events.hpp"
#include "game/eventhandlerpriority.hpp"
#include "game/skirmish/isometricconversion.hpp"
#include "game/skirmish/boardtoworldconversion.hpp"
#include "game/skirmish/unit.hpp"
#include "game/skirmish/structure.hpp"

namespace qrw
{

Cursor::Cursor()
	: SquareMarker(),
	  EventHandler(EventHandlerPriority::DEFAULT)
{}

Cursor::~Cursor()
{
}

bool Cursor::handleEvent(const IEvent& event)
{
	Coordinates newBoardPosition{-1, -1};
	if(event.getName() == MouseMovedEvent::name)
    {
		const MouseMovedEvent& moveEvent = static_cast<const MouseMovedEvent&>(event);

		GameObject* clickedObject = g_physicsEngine.pixelPerfectRaycast(moveEvent.worldCoordinates.x, moveEvent.worldCoordinates.y);
		if(clickedObject) {
			if(auto unit = dynamic_cast<Unit*>(clickedObject)) {
				newBoardPosition = unit->getBoardPosition();
			} else if (auto structure = dynamic_cast<Structure*>(clickedObject)) {
				newBoardPosition = structure->getPosition();
			}
		} else {
			newBoardPosition = worldToBoard(isoToWorld(sf::Vector2f(moveEvent.worldCoordinates)));
		}

		if(newBoardPosition != m_boardPosition)
		{
			Board* board = g_scene.findSingleGameObject<Board>();
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
