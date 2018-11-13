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

} // namespace qrw