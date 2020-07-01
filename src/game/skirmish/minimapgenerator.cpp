#include "game/skirmish/minimapgenerator.hpp"

#include <SFML/Graphics/Image.hpp>
#include <engine/terraintypes.hpp>

#include "engine/board.hpp"
#include "engine/terrain.hpp"
#include "game/deploymentzone.hpp"
#include "game/constants.hpp"
#include "game/skirmish/coordinates.hpp"

namespace qrw
{

void drawPixel(sf::Image* image, const Coordinates& boardPosition, const sf::Color& color)
{
	auto start = sf::Vector2u(boardPosition.getX() * 3, boardPosition.getY() * 3);
	for(size_t x = 0; x < 3; ++x) {
		for(size_t y = 0; y < 3; ++y) {
			sf::Vector2u currentPixel = start + sf::Vector2u(x, y);
			image->setPixel(currentPixel.x, currentPixel.y, color);
		}
	}
}

sf::Color getTerrainColor(TERRAINTYPES type) {
	if(type == TERRAINTYPES::ET_HILL) {
		return {88, 111, 88};
	} else if(type == TERRAINTYPES::ET_WOOD) {
		return {147, 62, 0};
	}
}

sf::Image* generateMiniMap(const MapDto& dto)
{
	sf::Vector2u imageSize = sf::Vector2u(dto.board->getWidth(), dto.board->getHeight()) * 3u;

	auto* image = new sf::Image();
	image->create(imageSize.x, imageSize.y, {81, 149, 81});

	for(auto& structureIter : dto.board->getStructures())
		drawPixel(image, structureIter.first, {128, 128, 128});

	for(auto& terrainIter : dto.board->getTerrains())
		drawPixel(image, terrainIter.first, getTerrainColor(terrainIter.second->getType()));

	return image;
}

}