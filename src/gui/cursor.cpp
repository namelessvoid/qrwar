#include <stdio.h>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "gui/cursor.hpp"

#include "engine/board.hpp"

namespace qrw
{
Cursor* Cursor::_cursor = 0;

Cursor::Cursor()
: RectangleShape(),
  _child(0),
  _maincolor(218, 218, 0, 120),
  _subcolor(218, 0, 0, 120),
  _boardPosition(0, 0)
{
    setFillColor(_maincolor);
    setSize({32.0f, 32.0f});
}

Cursor::~Cursor()
{}

Cursor* Cursor::getCursor()
{
    if(_cursor == 0)
        _cursor = new Cursor();
    return _cursor;
}

void Cursor::setBoard(std::shared_ptr<Board> spBoard)
{
    _spBoard = spBoard;
}

void Cursor::setDimensions(float dimensions)
{
    RectangleShape::setSize({dimensions, dimensions});
}

Cursor* Cursor::spawnChild()
{
    if(_child != 0)
            return 0;
    else
    {
        _child = new Cursor();
        _child->setBoard(_spBoard);
        _child->setSize(getSize());
        _child->setFillColor(_maincolor);
        this->setFillColor(_subcolor);
    }
    return _child;
}

Cursor* Cursor::getChild() const
{
        return _child;
}

void Cursor::despawnChild()
{
    if(_child != 0)
    {
        delete _child;
        _child = 0;
        this->setFillColor(_maincolor);
    }
}

void Cursor::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw((sf::RectangleShape)*this, states);
    if(getChild() != 0)
        target.draw(*getChild(), states);
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

        if(_spBoard->isOnBoard(newBoardPosition))
        {
            setPosition(newPosition);
            _boardPosition = newBoardPosition;
        }
    }
}

} // namespace qrwar
