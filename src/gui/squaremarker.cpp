#include "gui/squaremarker.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace qrw
{

SquareMarker::SquareMarker()
	: sf::RectangleShape(),
	  _color(218, 218, 0, 120),
	  _boardPosition(0, 0),
	  _visible(true)
{
	setFillColor(_color);
	setSize({32.0f, 32.0f});
}

void SquareMarker::setBoard(std::shared_ptr<Board> spBoard)
{
	_board = spBoard;
}

void SquareMarker::setDimensions(float dimensions)
{
	RectangleShape::setSize({dimensions, dimensions});
}

void SquareMarker::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if(_visible)
		target.draw((sf::RectangleShape)*this, states);
}

Coordinates SquareMarker::getBoardPosition()
{
	return _boardPosition;
}

bool SquareMarker::isVisible() const
{
	return _visible;
}

void SquareMarker::setVisible(bool visible)
{
	_visible = visible;
}

} // namespace qrw
