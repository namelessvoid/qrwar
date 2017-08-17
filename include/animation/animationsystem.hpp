#ifndef QRW_ANIMATIONSYSTEM_HPP
#define QRW_ANIMATIONSYSTEM_HPP

#include <set>
#include <cassert>

namespace qrw
{

class Animation;

class AnimationSystem
{
public:
    void addAnimation(Animation* animation);

    void removeAnimation(Animation* animation);

    void update(float deltaTime);

private:
    std::set<Animation*> m_animations;
};

extern AnimationSystem g_animationSystem;

} // namespace qrw

#endif // QRW_ANIMATIONSYSTEM_HPP
