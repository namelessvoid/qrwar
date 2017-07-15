#include "gui/squaremarker.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace qrw
{

SquareMarker::SquareMarker()
	: sf::RectangleShape(),
	  _boardPosition(0, 0),
	  _visible(true)
{
	setFillColor(sf::Color(218, 218, 0, 120));
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

Coordinates SquareMarker::getBoardPosition() const
{
	return _boardPosition;
}

void SquareMarker::setBoardPosition(const Coordinates& boardPosition)
{
	_boardPosition = boardPosition;

	float dimension = getSize().x;

	setPosition({dimension * _boardPosition.getX(), dimension * _boardPosition.getY()});
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
