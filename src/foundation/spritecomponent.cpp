#include "foundation/spritecomponent.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace qrw
{

SpriteComponent::SpriteComponent()
{
	_rectangle = new sf::RectangleShape();
}

SpriteComponent::~SpriteComponent()
{
	delete _rectangle;
}

void SpriteComponent::setTexture(const sf::Texture* texture)
{
	_rectangle->setTexture(texture);
}

void SpriteComponent::setSize(const sf::Vector2f& size)
{
	_rectangle->setSize(size);
}

void SpriteComponent::setPosition(const sf::Vector2f& position)
{
	_rectangle->setPosition(position);
}

void SpriteComponent::render(sf::RenderTarget *renderTarget)
{
	renderTarget->draw(*_rectangle);
}

} // namespace qrw
