#ifndef QRW_SPLASHSCREEN_HPP
#define QRW_SPLASHSCREEN_HPP

#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace qrw
{
	class SplashScreen : sf::Sprite
	{
		public:
			SplashScreen(std::string imgpath);
			~SplashScreen();

			void setCloseable(bool closeable = true);
			bool show();

		private:
			sf::Sprite* sprite;
			sf::Texture* spritetex;
			sf::RenderWindow* renderwindow;
			bool closeable;
	};
}
#endif