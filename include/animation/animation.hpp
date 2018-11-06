#ifndef QRW_ANIMATION_HPP
#define QRW_ANIMATION_HPP

#include "animation/animationsystem.hpp"

namespace qrw
{

class Animation
{
public:
    Animation()
		: m_isRunning(false),
		  durationInSeconds_(0),
		  m_currentRunTime(0)
    {
        g_animationSystem.addAnimation(this);
    }

    virtual ~Animation()
    {
        g_animationSystem.removeAnimation(this);
    }

	virtual void animate(float deltaTime)
	{
		if(!m_isRunning) return;

		if(m_currentRunTime >= durationInSeconds_)
		{
			stop();
			return;
		}

		m_currentRunTime += deltaTime;

		if(m_currentRunTime > durationInSeconds_)
		{
			m_currentRunTime = durationInSeconds_;
		}
	}

	virtual void start()
	{
		m_isRunning = true;
		m_currentRunTime = 0;
	}

	virtual void stop()
	{
		m_isRunning = false;
		m_currentRunTime = 0;
	}

	bool isRunning() const
	{
		return m_isRunning;
	}

	void setDuration(float durationInSeconds)
	{
		durationInSeconds_ = durationInSeconds;
	}

	float getDurationInSeconds() const
	{
		return durationInSeconds_;
	}

	float getCurrentRunTime() const
	{
		return m_currentRunTime;
	}

private:
	bool m_isRunning;

	float durationInSeconds_;

	float m_currentRunTime;
};

} // namespace qrw

#endif // QRW_ANIMATION_HPP
