#include "foundation/followrouteanimationcomponent.hpp"

#include <math.h>

#include "rendering/renderable.hpp"

namespace qrw
{

FollowRouteAnimationComponent::FollowRouteAnimationComponent(qrw::Renderable* renderable)
	: Animation(),
	  renderable_(renderable)
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

	float percentPerEdge = getDurationInSeconds() / (float)edgeCount;
	float currentEdgePercentage = (percentage - percentPerEdge * currentStartIndex) / percentPerEdge;

	sf::Vector2f newPosition = start + currentEdgePercentage * direction;
	renderable_->setPosition(newPosition);
}

} // namespace qrw