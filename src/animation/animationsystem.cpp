#include "animation/animationsystem.hpp"

#include "animation/animation.hpp"

namespace qrw
{

void AnimationSystem::addAnimation(Animation *animation)
{
	assert(animation!=nullptr);
	m_animations.insert(animation);
}

void AnimationSystem::removeAnimation(Animation *animation)
{
	assert(animation!=nullptr);
	m_animations.erase(animation);
}

void AnimationSystem::update(float deltaTime)
{
	for(Animation* animation : m_animations)
	{
		animation->animate(deltaTime);
	}
}

} // namespace qrw
