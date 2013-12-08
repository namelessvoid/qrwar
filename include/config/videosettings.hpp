#ifndef QRW_VIDEOSETTINGS_HPP
#define QRW_VIDEOSETTINGS_HPP

#include <string>
#include <tinyxml2.h>

#include "config/xmlhelper.hpp"

namespace qrw
{
	class VideoSettings : public XMLHelper
	{
		public:
			VideoSettings();
			~VideoSettings();

			bool loadFromFile(std::string path);

			void setResolutionX(int resolutionX);
			int getResolutionX();

			void setResolutionY(int resolutionY);
			int getResolutionY();

			void setFullscreen(bool fullscreen);
			bool getFullscreen();

			void setTilesetPath(std::string tilesetpath);
			std::string getTilesetPath();

			tinyxml2::XMLElement* toTinyxml2Element(tinyxml2::XMLDocument* document);

		protected:
			int resolutionX;
			int resolutionY;
			bool fullscreen;
			std::string tilesetpath;
	};
}
#endif