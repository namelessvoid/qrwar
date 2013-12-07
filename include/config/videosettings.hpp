#ifndef QRW_VIDEOSETTINGS_HPP
#define QRW_VIDEOSETTINGS_HPP

#include <string>

namespace qrw
{
	class VideoSettings
	{
		public:
			VideoSettings();
			~VideoSettings();

			bool loadFromFile(std::string path);

		protected:
			int resolutionX;
			int resolutionY;
			bool fullscreen;
	};
}
#endif