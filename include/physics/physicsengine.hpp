#ifndef QRW_PHYSICSENGINE_HPP
#define QRW_PHYSICSENGINE_HPP

#include <vector>
#include <map>
#include <memory>

#include <SFML/Graphics/Texture.hpp>

#include "foundation/spritecomponent.hpp"

#include "physics/texturealphamask.hpp"

namespace qrw {

class PhysicsEngine
{
public:
	PhysicsEngine() = default;

	~PhysicsEngine() = default;

	PhysicsEngine(const PhysicsEngine& rhs) = delete;
	PhysicsEngine& operator=(const PhysicsEngine& rhs) = delete;

	void registerSpriteComponent(const SpriteComponent& component);
	void deregisterSpriteCompnent(const SpriteComponent& component);

	/**
	 * Performs ray cast like pixel-perfect collision detection for a given point.
	 *
	 * Since this is pixel perfect, the cast is performed
	 * on qrw::SpriteComponents only. The ray is cast into the screen from top to bottom. This means that SpriteComponents
	 * with higher z-index are tested first.
	 *
	 * @param originX The x position of the ray in world coordinates.
	 * @param originY The y position of the ray in world coordinates.
	 * @return The object being hit.
	 */
	GameObject* pixelPerfectRaycast(float originX, float originY);

private:
	std::vector<const SpriteComponent*> registeredSpriteComponents_;

	std::map<const sf::Texture*, std::unique_ptr<TextureAlphaMask>> textureAlphaMasks_;
};

extern PhysicsEngine g_physicsEngine;

} // namespace qrw

#endif // QRW_PHYSICSENGINE_HPP