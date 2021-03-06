#include "foundation/followrouteanimationcomponent.hpp"

#include <cmath>

#include "rendering/renderable.hpp"

#include "game/skirmish/unit.hpp"

namespace qrw
{

FollowRouteAnimationComponent::FollowRouteAnimationComponent(Unit* unit)
	: GameComponent(*unit),
	  Animation(),
	  unit_(unit)
{
	setDuration(1);
}

void FollowRouteAnimationComponent::start()
{
	assert(corners_.size() >= 2);
	Animation::start();
}

void FollowRouteAnimationComponent::stop()
{
	Animation::stop();
	corners_.clear();
}

void FollowRouteAnimationComponent::animate(float deltaTime)
{
	Animation::animate(deltaTime);

	if(!isRunning()) return;

	// TODO: Ensure corners_.size() > 0
	size_t edgeCount = (corners_.size() - 1);

	float percentage = getCurrentRunTime() / getDurationInSeconds();
	percentage = percentage > 1 ? 1 : percentage;
	percentage = percentage < 0 ? 0 : percentage;

	size_t currentStartIndex = (size_t)std::floor(edgeCount * percentage);
	size_t currentEndIndex   = (size_t)std::ceil(edgeCount * percentage);

	sf::Vector2f start = corners_[currentStartIndex];
	sf::Vector2f end   = corners_[currentEndIndex];
	sf::Vector2f direction = end - start;

	float timePerEdge = getDurationInSeconds() / (float)edgeCount;
	float currentEdgeTime = (getCurrentRunTime() - timePerEdge * currentStartIndex);
	float currentEdgePercentage =  currentEdgeTime / timePerEdge;

	sf::Vector2f newPosition = start + currentEdgePercentage * direction;
	unit_->setWorldPosition(newPosition);
}

} // namespace qrw