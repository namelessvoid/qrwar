#ifndef QRW_IMAGEMANAGER_HPP
#define QRW_IMAGEMANAGER_HPP

#include <string>
#include <map>

#include <SFML/Graphics/Image.hpp>

namespace qrw
{

	class ImageManager
	{
		public:
			~ImageManager();

			static ImageManager& getInstance();
			bool loadImage(const std::string texname, const std::string filepath);
			const sf::Image* getImage(const std::string imgname);

		private:
			ImageManager();
			static ImageManager* imagemanager;
			std::map<std::string, sf::Image*> images;
	};
}

#endif