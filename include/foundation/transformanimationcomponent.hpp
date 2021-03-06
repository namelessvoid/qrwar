#ifndef QRW_TRANSFORMANIMATIONCOMPONENT_HPP
#define QRW_TRANSFORMANIMATOINCOMPONENT_HPP

#include "animation/animation.hpp"

#include "foundation/spritecomponent.hpp"

namespace qrw
{

class TransformAnimationComponent : public Animation, public GameComponent
{
public:
    TransformAnimationComponent(GameObject& owner, Renderable* animationTarget)
    	: GameComponent(owner)
    {
        assert(animationTarget!=nullptr);
        m_animationTarget = animationTarget;
    }

    virtual void animate(float deltaTime) override
    {
		Animation::animate(deltaTime);

		if(!isRunning())
			return;

        sf::Vector2f positionDelta = sf::Vector2f(0, -32) * deltaTime;
        m_animationTarget->setPosition(m_animationTarget->getPosition() + positionDelta);
    }

private:
    Renderable* m_animationTarget;
};

} // namespace qrw

#endif // QRW_TRANSFORMANIMATIONCOMPONENT_HPP
