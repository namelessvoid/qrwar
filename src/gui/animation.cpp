#include "gui/animation.hpp"

#include <stdio.h>

namespace qrw
{
	std::vector<Animation*> Animation::animations;

	void Animation::renderAll(sf::RenderTarget& target, sf::Time elapsedtime, sf::RenderStates states)
	{
		/*for(auto iter = animations.begin(); iter != animations.end(); ++iter)
		{
			(*iter)->update(elapsedtime);
		}*/
		for(int i = animations.size() - 1; i >= 0; --i)
		{
			animations.at(i)->update(elapsedtime);
		}
		for(auto iter = animations.begin(); iter != animations.end(); ++iter)
		{
			(*iter)->draw(target, states);
		}
	}
	Animation::Animation(float duration, bool loop, bool deleteonstop)
		: duration(duration),
		  loop(loop),
		  deleteonstop(deleteonstop),
		  totalelapsedtime(0.0f)
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
		totalelapsedtime = 0.0f;
		status = S_PLAYING;
	}

	void Animation::stop()
	{
		if(deleteonstop)
			delete this;
		else
		{
			totalelapsedtime = 0.0f;
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

	void Animation::update(sf::Time elapsedtime)
	{
		totalelapsedtime = totalelapsedtime + elapsedtime.asSeconds();
		printf("Animation::update(): elapsed / total: %f / %f\n", elapsedtime.asSeconds(), totalelapsedtime);

		if(totalelapsedtime > duration)
		{
			if(!loop)
				stop();
			else
				totalelapsedtime = totalelapsedtime - duration;
		}
	}


}