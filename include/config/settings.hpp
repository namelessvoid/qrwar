#ifndef QRW_SETTINGS_HPP
#define QRW_SETTINGS_HPP

#include "config/videosettings.hpp"
#include "config/audiosettings.hpp"

namespace qrw
{
	class Settings : public VideoSettings, AudioSettings
	{
		public:
			Settings();
			~Settings();
	};
}
#endif