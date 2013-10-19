#ifndef QRW_ANIMATION_HPP
#define QRW_ANIMATION_HPP

#include <vector>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>

namespace qrw
{

	/**
	 * @brief Abstract class for managing animations.
	 */
	class Animation : public sf::Drawable
	{
		public:
			static void renderAll(sf::RenderTarget& target, sf::Time elapsedTime, sf::RenderStates states = sf::RenderStates::Default);

			/**
			 * @brief Create a new animation.
			 *
			 * @param duration The duration of the animation in seconds.
			 * @param deleteonstop If set to true the Animation is deleted when stop() is called
			 *					   or the animation ended.
			 */
			Animation(float duration = 1.0f, bool loop = false, bool deleteonstop = false);
			~Animation();

			void start();
			void stop();
			void pause();
			void resume();

			virtual void update(sf::Time elapsedTime) = 0;

		private:
			enum STATES
			{
				S_STOPPED,
				S_PLAYING,
				S_PAUSED,
			};

			/*
			 * This vector holds pointers to all existing animations. A animation registers itself in
			 * its constructor and removes itself in its destructor.
			 */
			static std::vector<Animation*> animations;

			float duration;
			bool loop;
			bool deleteonstop;

			STATES status;
			float totalElapsedTime;
	};
}
#endif