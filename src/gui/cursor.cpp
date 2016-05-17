#include <stdio.h>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "gui/cursor.hpp"

#include "engine/board.hpp"

namespace qrw
{

Cursor::Cursor()
	: RectangleShape(),
	  _maincolor(218, 218, 0, 120),
	  _visible(true),
	  _boardPosition(0, 0)
{
    setFillColor(_maincolor);
    setSize({32.0f, 32.0f});
}

Cursor::~Cursor()
{
}

void Cursor::setBoard(std::shared_ptr<Board> spBoard)
{
    _spBoard = spBoard;
}

void Cursor::setDimensions(float dimensions)
{
    RectangleShape::setSize({dimensions, dimensions});
}

void Cursor::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if(_visible)
		target.draw((sf::RectangleShape)*this, states);
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
            if(_spBoard->isOnBoard(newBoardPosition))
            {
                setPosition(newPosition);
                 _visible = true;
            }
            else
            {
                _visible = false;
            }

            _boardPosition = newBoardPosition;
            signalMoved.emit(_boardPosition, _visible);
        }
    }
	else if( _visible == true && event.type == sf::Event::MouseButtonPressed)
	{
		if(event.mouseButton.button == sf::Mouse::Button::Left)
			signalLeftClicked.emit(_boardPosition);
		else if(event.mouseButton.button == sf::Mouse::Button::Right)
			signalRightClicked.emit(_boardPosition);
    }
}

Coordinates Cursor::getBoardPosition()
{
    return _boardPosition;
}

} // namespace qrwar
