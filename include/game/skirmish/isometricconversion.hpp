#ifndef QRW_ISOMETRICCONVERSION_HPP
#define QRW_ISOMETRICCONVERSION_HPP

#include <SFML/System/Vector2.hpp>

namespace qrw
{

// Convert provided world position into isometric view coordinates.
sf::Vector2f worldToIso(sf::Vector2f worldPosition);

// Convert the provided isometric view coordinates into world positions.
sf::Vector2f isoToWorld(sf::Vector2f isometricPosition);

}

#endif //QRW_ISOMETRICCONVERSION_HPP
