#include "foundation/spritecomponent.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "rendering/rendersystem.hpp"
#include "physics/physicsengine.hpp"

namespace qrw
{

SpriteComponent::SpriteComponent(GameObject& owner, Layer layer)
	: GameComponent(owner),
	  Renderable(layer),
	  _rectangle(new sf::RectangleShape()),
	  physicsEnabled_(false)
{
}

SpriteComponent::~SpriteComponent()
{
	if(physicsEnabled_)
		disablePhysics();

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
	setZIndex(position.y);
}

const sf::Vector2f& SpriteComponent::getPosition() const
{
	return _rectangle->getPosition();
}

void SpriteComponent::setFillColor(const sf::Color &color)
{
	_rectangle->setFillColor(color);
}

void SpriteComponent::render(sf::RenderTarget &renderTarget)
{
	if(!isVisible()) return;

	renderTarget.draw(*_rectangle);
}

sf::FloatRect SpriteComponent::getGlobalBounds() const
{
	return _rectangle->getGlobalBounds();
}

void SpriteComponent::enablePhysics()
{
	assert(!physicsEnabled_);
	physicsEnabled_ = true;
	g_physicsEngine.registerSpriteComponent(*this);
}

void SpriteComponent::disablePhysics()
{
	assert(physicsEnabled_);
	g_physicsEngine.deregisterSpriteCompnent(*this);
	physicsEnabled_ = false;
}

} // namespace qrw
