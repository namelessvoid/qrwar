#include "game/deploymentzone.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "game/renderlayers.hpp"
#include "game/constants.hpp"

namespace qrw
{

SID DeploymentZone::typeName("qrw::DeploymentZone");

DeploymentZone::DeploymentZone()
    : Renderable(RENDER_LAYER_DEPLOYMENT_ZONE),
      playerId_(-1),
      color_(sf::Color::Green)
{
}

DeploymentZone::~DeploymentZone()
{
}

void DeploymentZone::render(sf::RenderTarget& renderTarget)
{
    sf::RectangleShape rectangle;
    rectangle.setSize({SQUARE_DIMENSION, SQUARE_DIMENSION});
    rectangle.setFillColor(color_);

    for(auto& coordinate : zone_)
    {
        rectangle.setPosition({SQUARE_DIMENSION * coordinate.getX(), SQUARE_DIMENSION * coordinate.getY()});
        renderTarget.draw(rectangle);
    }
}

void DeploymentZone::setPosition(const sf::Vector2f& position)
{
    position_ = position;
}

const sf::Vector2f& DeploymentZone::getPosition() const
{
    return position_;
}

void DeploymentZone::addSquare(const Coordinates& coordinate)
{
    zone_.insert(coordinate);
}

void DeploymentZone::removeSquare(const Coordinates& coordinate)
{
    zone_.erase(coordinate);
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
