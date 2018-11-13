#include "foundation/spritecomponent.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "rendering/rendersystem.hpp"

namespace qrw
{

SpriteComponent::SpriteComponent(Layer layer)
	: Renderable(layer)
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
	_rectangle->setTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));
}

void SpriteComponent::setSize(const sf::Vector2f& size)
{
	_rectangle->setSize(size);
}

const sf::Vector2f &SpriteComponent::getSize()
{
	return _rectangle->getSize();
}

void SpriteComponent::setPosition(const sf::Vector2f& position)
{
	_rectangle->setPosition(position);
}

const sf::Vector2f& SpriteComponent::getPosition() const
{
	return _rectangle->getPosition();
}

sf::Vector2f SpriteComponent::getCenter()
{
	return getPosition() + getSize() * 0.5f;
}

void SpriteComponent::setFillColor(const sf::Color &color)
{
	_rectangle->setFillColor(color);
}

void SpriteComponent::render(sf::RenderTarget &renderTarget)
{
	renderTarget.draw(*_rectangle);
}

} // namespace qrw
