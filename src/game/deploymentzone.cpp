#include "game/deploymentzone.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "gui/texturemanager.hpp"
#include "gui/scene.hpp"
#include "game/renderlayers.hpp"
#include "game/constants.hpp"
#include "game/skirmish/wall.hpp"
#include "game/skirmish/isometricconversion.hpp"
#include "game/skirmish/boardtoworldconversion.hpp"

namespace qrw
{

const SID DeploymentZone::typeName("qrw::DeploymentZone");

DeploymentZone::DeploymentZone()
    : GameObject(),
      playerId_(-1),
      color_(sf::Color::Green)
{
}

//void DeploymentZone::render(sf::RenderTarget& renderTarget)
//{
//    sf::CircleShape rectangle(SQUARE_DIMENSION, 4);
//    rectangle.scale({1.0f, 0.5f});
//    rectangle.setOrigin({SQUARE_DIMENSION, 0.0f});
//
//    rectangle.setFillColor(color_);
//
//    for(auto& coordinate : zone_)
//    {
//    	float heightOffset = 0;
//
//    	Board* board = g_scene.findSingleGameObject<Board>();
//    	if(auto* structure = board->getStructure(coordinate)) {
//    		if(dynamic_cast<Wall*>(structure) != nullptr) {
//    			heightOffset = -2.0f * SQUARE_DIMENSION;
//    		}
//    	}
//
//        rectangle.setPosition(worldToIso(boardToWorld(coordinate)));
//        rectangle.move({0, heightOffset});
//        renderTarget.draw(rectangle);
//    }
//}

void DeploymentZone::addSquare(const Coordinates& coordinates)
{
	assert(zone_.find(coordinates) == zone_.end());

    zone_.insert(coordinates);

    auto* sprite = new SpriteComponent(RENDER_LAYER_GAME);
    sprite->setTexture(TextureManager::getInstance()->getTexture("deploymentzone"));
    sprite->setFillColor(color_);
    sprite->setOrigin(SQUARE_DIMENSION, 0.0f);
    sprite->setSize({2.0f * SQUARE_DIMENSION, SQUARE_DIMENSION});
    sprite->setPosition(worldToIso(boardToWorld(coordinates)));

    addComponent(sprite);
    sprites_[coordinates] = sprite;
}

void DeploymentZone::removeSquare(const Coordinates& coordinates)
{
	assert(zone_.find(coordinates) != zone_.end());

    zone_.erase(coordinates);

    auto* sprite = sprites_[coordinates];
    removeComponent(sprite);
    sprites_.erase(coordinates);
    delete sprite;
}

bool DeploymentZone::containsSquare(const Coordinates& coordinate)
{
    return zone_.find(coordinate) != zone_.end();
}

void qrw::DeploymentZone::crop(const Coordinates& size)
{
	auto iter = zone_.begin();
	while(iter != zone_.end())
	{
		Coordinates square = *iter;
		if(square.getX() >= size.getX() || square.getY() >= size.getY())
			iter = zone_.erase(iter);
		else
			++iter;
	}
}

void DeploymentZone::setPlayerId(int playerId)
{
    playerId_ = playerId;

    switch(playerId)
    {
        case 1: color_ = PLAYER_ONE_COLOR; break;
        case 2: color_ = PLAYER_TWO_COLOR; break;
        default: assert(playerId == 1 || playerId == 2);
    }
}

} // namespace qrw
