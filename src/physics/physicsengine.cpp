#include <cassert>
#include <iostream>

#include "physics/physicsengine.hpp"
#include "rendering/renderablezindexcomparer.hpp"

namespace qrw
{

void PhysicsEngine::registerSpriteComponent(const SpriteComponent& component)
{
	assert(std::find(registeredSpriteComponents_.begin(), registeredSpriteComponents_.end(), &component) == registeredSpriteComponents_.end());

	registeredSpriteComponents_.push_back(&component);
}

void PhysicsEngine::deregisterSpriteCompnent(const qrw::SpriteComponent& component)
{
	auto iterator = std::find(registeredSpriteComponents_.begin(), registeredSpriteComponents_.end(), &component);
	assert(iterator != registeredSpriteComponents_.end());
	registeredSpriteComponents_.erase(iterator);
}

GameObject* PhysicsEngine::pixelPerfectRaycast(float originX, float originY)
{
	// required:
	// - Texture
	// - Texture Rect
	// - GlobalBounds
	// - Reverse transform

	std::cout << "alpha masks size: " << textureAlphaMasks_.size() << std::endl << std::flush;

	std::sort(registeredSpriteComponents_.begin(), registeredSpriteComponents_.end(), RenderableZIndexComparerGreater);

	for(auto& spriteComponent : registeredSpriteComponents_) {
		if(!spriteComponent->isVisible())
			continue;

		auto bounds = spriteComponent->getGlobalBounds();
		if(!bounds.contains(originX, originY))
			continue;

		const TextureAlphaMask& textureAlphaMask = getOrCreateAlphaMaskForTexture(*spriteComponent->getTexture());
		sf::IntRect textureRect = spriteComponent->getTextureRect();
		sf::Vector2f originInSpriteCoordinates = spriteComponent->getInverseTransform().transformPoint(originX, originY);
		bool isPixel = textureAlphaMask.isPixelSet(
				(int)(originInSpriteCoordinates.x) + textureRect.left,
				(int)(originInSpriteCoordinates.y) + textureRect.top);
		if(!isPixel)
			continue;

		return spriteComponent->getOwner();
	}

	return nullptr;
}

const TextureAlphaMask& PhysicsEngine::getOrCreateAlphaMaskForTexture(const sf::Texture& texture)
{
	auto iter = textureAlphaMasks_.find(&texture);
	if(iter == textureAlphaMasks_.end()) {
		iter = textureAlphaMasks_.insert(std::make_pair(&texture, std::make_unique<TextureAlphaMask>(texture))).first;
	}

	return *iter->second;
}

} // namespace qrw
