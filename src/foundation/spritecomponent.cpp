#include "foundation/spritecomponent.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "rendering/rendersystem.hpp"

namespace qrw
{

SpriteComponent::SpriteComponent(Layer layer)
	: Renderable(layer)
{
	_rectangle = new sf::RectangleShape();
	g_renderSystem.registerRenderable(this);
}

SpriteComponent::~SpriteComponent()
{
	g_renderSystem.deregisterRenderable(this);
	delete _rectangle;
}

void SpriteComponent::setTexture(const sf::Texture* texture)
{
	_rectangle->setTexture(texture);
}

void SpriteComponent::setRepeateTexture(bool repeate)
{
	const sf::Vector2f& size = repeate ? _rectangle->getSize() : static_cast<sf::Vector2f>(_rectangle->getTexture()->getSize());
	_rectangle->setTextureRect(sf::IntRect(0, 0, size.x, size.y));
}

void SpriteComponent::setSize(const sf::Vector2f& size)
{
	_rectangle->setSize(size);
}

void SpriteComponent::setPosition(const sf::Vector2f& position)
{
	_rectangle->setPosition(position);
}

const sf::Vector2f& SpriteComponent::getPosition() const
{
	return _rectangle->getPosition();
}

void SpriteComponent::render(sf::RenderTarget &renderTarget)
{
	renderTarget.draw(*_rectangle);
}

} // namespace qrw
