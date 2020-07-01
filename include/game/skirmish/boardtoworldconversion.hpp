#ifndef QRW_BOARDTOWORLDCONVERSION_HPP
#define QRW_BOARDTOWORLDCONVERSION_HPP

#include <SFML/System/Vector2.hpp>

#include "coordinates.hpp"

namespace qrw
{

sf::Vector2f boardToWorld(const Coordinates& boardPosition);
Coordinates worldToBoard(const sf::Vector2f& worldPosition);

} // namespace qrw

#endif //QRW_BOARDTOWORLDCONVERSION_HPP
