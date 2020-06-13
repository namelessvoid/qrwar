#include <cassert>
#include <iostream>

#include "physics/physicsengine.hpp"
#include "rendering/renderablezindexcomparer.hpp"

namespace qrw
{

void PhysicsEngine::registerSpriteComponent(const SpriteComponent& component)
{
	assert(std::find(registeredSpriteComponents_.begin(), registeredSpriteComponents_.end(), &component) == registeredSpriteComponents_.end());

	const sf::Texture* texture = component.getTexture();
	if(textureAlphaMasks_.find(texture) == textureAlphaMasks_.end()) {
		textureAlphaMasks_.insert(std::make_pair(texture, std::make_unique<TextureAlphaMask>(*texture)));
	}

	registeredSpriteComponents_.push_back(&component);
	std::sort(registeredSpriteComponents_.begin(), registeredSpriteComponents_.end(), RenderableZIndexComparerGreater);
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

	for(auto& spriteComponent : registeredSpriteComponents_) {
		if(!spriteComponent->isVisible())
			continue;

		auto bounds = spriteComponent->getGlobalBounds();
		if(!bounds.contains(originX, originY))
			continue;

		std::unique_ptr<TextureAlphaMask>& textureAlphaMask = textureAlphaMasks_[spriteComponent->getTexture()];
		sf::IntRect textureRect = spriteComponent->getTextureRect();
		sf::Vector2f originInSpriteCoordinates = spriteComponent->getInverseTransform().transformPoint(originX, originY);
		bool isPixel = textureAlphaMask->isPixelSet(
				(int)(originInSpriteCoordinates.x) + textureRect.left,
				(int)(originInSpriteCoordinates.y) + textureRect.top);
		if(!isPixel)
			continue;

		return spriteComponent->getOwner();
	}

	return nullptr;
}

} // namespace qrw
