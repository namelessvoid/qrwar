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
		m_currentRunTime = 0;
		m_duration = 0;
		m_isRunning = true;
    }

    virtual ~Animation()
    {
        g_animationSystem.removeAnimation(this);
    }

	virtual void animate(float deltaTime)
	{
		m_currentRunTime += deltaTime;

		if(m_currentRunTime >= m_duration)
			m_isRunning = false;
	}

	bool isRunning()
	{
		return m_isRunning;
	}

	void setDuration(float duration)
	{
		m_duration = duration;
	}

private:
	bool m_isRunning;

	float m_duration;

	float m_currentRunTime;
};

} // namespace qrw

#endif // QRW_ANIMATION_HPP
