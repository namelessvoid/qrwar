#ifndef QRW_ISOMETRICCONVERSION_HPP
#define QRW_ISOMETRICCONVERSION_HPP

#include <SFML/System/Vector2.hpp>

namespace qrw
{

sf::Vector2f worldToIso(sf::Vector2f worldPosition);
sf::Vector2f isoToWorld(sf::Vector2f isometricPosition);

}

#endif //QRW_ISOMETRICCONVERSION_HPP
