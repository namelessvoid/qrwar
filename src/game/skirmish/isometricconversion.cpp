#include "game/skirmish/isometricconversion.hpp"

#include "game/constants.hpp"

namespace qrw
{

sf::Vector2f worldToIso(sf::Vector2f worldPosition)
{
	return {
		 worldPosition.x - worldPosition.y,
		(worldPosition.x + worldPosition.y) / 2.0f
	};
}

sf::Vector2f isoToWorld(sf::Vector2f isometricPosition)
{
	return {
		(2 * isometricPosition.y + isometricPosition.x) / 2,
		(2 * isometricPosition.y - isometricPosition.x) / 2
	};
}

} // namespace qrw