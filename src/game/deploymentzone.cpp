#include "game/deploymentzone.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "game/renderlayers.hpp"

namespace qrw
{

DeploymentZone::DeploymentZone()
    : Renderable(RENDER_LAYER_DEPLOYMENT_ZONE),
      color_(sf::Color::Green)
{
}

DeploymentZone::~DeploymentZone()
{
}

void DeploymentZone::render(sf::RenderTarget& renderTarget)
{
    sf::RectangleShape rectangle;
    rectangle.setSize({32, 32});
    rectangle.setFillColor(color_);

    for(auto& coordinate : zone_)
    {
        rectangle.setPosition({32 * coordinate.getX(), 32 * coordinate.getY()});
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

void DeploymentZone::setColor(const sf::Color& color)
{
    color_ = color;
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

} // namespace qrw
