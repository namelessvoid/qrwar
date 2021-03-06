#ifndef QRW_SETTINGS_HPP
#define QRW_SETTINGS_HPP

#include <string>

#include "config/videosettings.hpp"
#include "config/audiosettings.hpp"

namespace qrw
{
	class Settings : public VideoSettings, public AudioSettings
	{
		public:
			~Settings();

			static Settings* getInstance();

			bool loadFromFile(std::string filepath = "");
			int saveToFile(std::string filepath = "");

		private:
			std::string defaultsettingspath = "res/conf/settings.xml";
			Settings();

			static Settings* instance;
	};
}
#endif
