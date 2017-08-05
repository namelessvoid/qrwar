#include <stdio.h>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "gui/cursor.hpp"

#include "engine/board.hpp"

#include "eventsystem/eventsystem.hpp"

namespace qrw
{

Cursor::Cursor()
	: SquareMarker()
{}

Cursor::~Cursor()
{
}

void Cursor::handleEvent(const sf::Event& event)
{
    if(event.type == sf::Event::MouseMoved)
    {
        sf::Vector2f newPosition;
        sf::Vector2f size = getSize();

        newPosition.x = event.mouseMove.x - (event.mouseMove.x % (int)size.x);
        newPosition.y = event.mouseMove.y - (event.mouseMove.y % (int)size.y);

        Coordinates newBoardPosition((int)newPosition.x / size.x, (int)newPosition.y / size.y);

        if(newBoardPosition != _boardPosition)
        {
			if(_board->isOnBoard(newBoardPosition))
            {
				setBoardPosition(newBoardPosition);
                 _visible = true;
            }
            else
            {
                _visible = false;
            }

			//signalMoved.emit(_boardPosition, _visible);
			g_eventSystem.pushEvent({Event::CursorMoved, _boardPosition});
        }
    }
	else if( _visible == true && event.type == sf::Event::MouseButtonPressed)
	{
		if(event.mouseButton.button == sf::Mouse::Button::Left)
			g_eventSystem.pushEvent({Event::CursorLeftClicked, _boardPosition});
		else if(event.mouseButton.button == sf::Mouse::Button::Right)
			g_eventSystem.pushEvent({Event::CursorRightClicked, _boardPosition});
	}
}

void Cursor::setFillColor(Cursor::Color color)
{
	sf::Color newColor;
	switch(color)
	{
	case Color::ESC_DEFAULT:
		newColor = sf::Color(218, 218, 0, 120);
		break;
	case Color::ESC_WARNING:
		newColor = sf::Color(218, 100, 100, 120);
		break;
	case Color::ESC_DANGER:
		newColor = sf::Color(218, 0, 0, 120);
		break;
	}

	SquareMarker::setFillColor(newColor);
}

} // namespace qrwar
