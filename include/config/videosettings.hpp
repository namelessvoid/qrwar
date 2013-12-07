#ifndef QRW_VIDEOSETTINGS_HPP
#define QRW_VIDEOSETTINGS_HPP

#include <string>

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

		protected:
			int resolutionX;
			int resolutionY;
			bool fullscreen;
	};
}
#endif