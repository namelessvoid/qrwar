#ifndef QRW_MINIMAPGENERATOR_HPP
#define QRW_MINIMAPGENERATOR_HPP

#include <SFML/Graphics/Image.hpp>

#include "game/skirmish/mapdto.hpp"

namespace qrw
{

sf::Image* generateMiniMap(const MapDto& mapDto);

}

#endif
