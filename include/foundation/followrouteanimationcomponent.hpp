#ifndef QRW_FOLLOWROUTECOMPONENT_HPP
#define QRW_FOLLOWROUTECOMPONENT_HPP

#include <vector>

#include <SFML/System/Vector2.hpp>

#include "animation/animation.hpp"
#include "foundation/gamecomponent.hpp"

namespace qrw
{
class Renderable;

class FollowRouteAnimationComponent : public GameComponent, public Animation
{
public:
	explicit FollowRouteAnimationComponent(class Unit* unit);

	void start() override;

	void stop() override;

	void animate(float deltaTime) override;

	// Add a new corner to the animation path. Note that this has to be in world coordinates.
	void addCorner(const sf::Vector2f worldPosition) { corners_.push_back(worldPosition); }

private:
	class Unit* unit_;

	std::vector<sf::Vector2f> corners_;
};

} // namespace qrw

#endif // QRW_FOLLOWROUTECOMPONENT_HPP
