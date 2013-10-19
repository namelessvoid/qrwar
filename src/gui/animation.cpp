#include "gui/animation.hpp"

namespace qrw
{
	std::vector<Animation*> Animation::animations;

	Animation::Animation(float duration, bool loop, bool deleteonstop)
		: duration(duration),
		  loop(loop),
		  deleteonstop(deleteonstop)
	{
		// Register animation to the animations vector.
		animations.push_back(this);
	}

	Animation::~Animation()
	{
		// Remove animation from animations vector.
		for(auto iter = animations.begin(); iter != animations.end(); ++iter)
		{
			if(*iter == this)
			{
				animations.erase(iter);
				break;
			}
		}
	}

	void Animation::start()
	{
		totalElapsedTime = 0.0f;
		status = S_PLAYING;
	}

	void Animation::stop()
	{
		if(deleteonstop)
			delete this;
		else
		{
			totalElapsedTime = 0.0f;
			status = S_STOPPED;
		}
	}

	void Animation::pause()
	{
		status = S_PAUSED;
	}

	void Animation::resume()
	{
		status = S_PLAYING;
	}

	void Animation::update(sf::Time elapsedTime)
	{
		totalElapsedTime += elapsedTime.asSeconds();

		if(totalElapsedTime > duration && !loop)
			stop();
		else
			totalElapsedTime = totalElapsedTime - duration;
	}

}