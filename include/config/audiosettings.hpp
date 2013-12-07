#ifndef QRW_AUDIOSETTINGS_HPP
#define QRW_AUDIOSETTINGS_HPP

#include <string>

namespace qrw
{
	class AudioSettings
	{
		public:
			bool loadFromFile(std::string filepath);
	};
}

#endif
