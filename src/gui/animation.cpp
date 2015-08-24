#include "gui/animation.hpp"

namespace qrw
{
	std::vector<Animation*> Animation::_animations;

	void Animation::renderAll(sf::RenderTarget& target, sf::Time elapsedtime, sf::RenderStates states)
	{
		/*for(auto iter = animations.begin(); iter != animations.end(); ++iter)
		{
			(*iter)->update(elapsedtime);
		}*/
		for(int i = _animations.size() - 1; i >= 0; --i)
		{
			_animations.at(i)->update(elapsedtime);
		}
		for(auto iter = _animations.begin(); iter != _animations.end(); ++iter)
		{
			(*iter)->draw(target, states);
		}
	}
	Animation::Animation(float duration, bool loop, bool deleteonstop)
		: _duration(duration),
		  _loop(loop),
		  _deleteonstop(deleteonstop),
		  _totalelapsedtime(0.0f)
	{
		// Register animation to the animations vector.
		_animations.push_back(this);
	}

	Animation::~Animation()
	{
		// Remove animation from animations vector.
		for(auto iter = _animations.begin(); iter != _animations.end(); ++iter)
		{
			if(*iter == this)
			{
				_animations.erase(iter);
				break;
			}
		}
	}

	void Animation::start()
	{
		_totalelapsedtime = 0.0f;
		_status = S_PLAYING;
	}

	void Animation::stop()
	{
		if(_deleteonstop)
			delete this;
		else
		{
			_totalelapsedtime = 0.0f;
			_status = S_STOPPED;
		}
	}

	void Animation::pause()
	{
		_status = S_PAUSED;
	}

	void Animation::resume()
	{
		_status = S_PLAYING;
	}

	void Animation::update(sf::Time elapsedtime)
	{
		_totalelapsedtime = _totalelapsedtime + elapsedtime.asSeconds();

		if(_totalelapsedtime > _duration)
		{
			if(!_loop)
				stop();
			else
				_totalelapsedtime = _totalelapsedtime - _duration;
		}
	}


}
