#include <cmath>

#include "game/constants.hpp"
#include "game/skirmish/boardtoworldconversion.hpp"

namespace qrw
{

sf::Vector2f boardToWorld(const Coordinates& boardPosition)
{
	return {(float)boardPosition.getX() * SQUARE_DIMENSION, (float)boardPosition.getY() * SQUARE_DIMENSION};
}

Coordinates worldToBoard(const sf::Vector2f& worldPosition)
{
	sf::Vector2f boardCoordinates = worldPosition / SQUARE_DIMENSION;
	boardCoordinates.x = std::ceil(boardCoordinates.x);
	boardCoordinates.y = std::ceil(boardCoordinates.y);

	return Coordinates(boardCoordinates.x, boardCoordinates.y);
}

}