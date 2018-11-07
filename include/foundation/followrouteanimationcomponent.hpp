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
	explicit FollowRouteAnimationComponent(Renderable* renderable);

	void start() override;

	void stop() override;

	void animate(float deltaTime) override;

	void addCorner(const sf::Vector2f edge) { corners_.push_back(edge); }

private:
	Renderable* renderable_;

	std::vector<sf::Vector2f> corners_;
};

} // namespace qrw

#endif // QRW_FOLLOWROUTECOMPONENT_HPP
