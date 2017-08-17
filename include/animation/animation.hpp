#ifndef QRW_ANIMATION_HPP
#define QRW_ANIMATION_HPP

#include "animation/animationsystem.hpp"

namespace qrw
{

class Animation
{
public:
    Animation()
    {
        g_animationSystem.addAnimation(this);
    }

    virtual ~Animation()
    {
        g_animationSystem.removeAnimation(this);
    }

    virtual void animate(float deltaTime) = 0;
};

} // namespace qrw

#endif // QRW_ANIMATION_HPP
