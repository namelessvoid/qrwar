#include "config/videosettings.hpp"

namespace qrw
{
	VideoSettings::VideoSettings()
		:	resolutionX(800),
			resolutionY(600),
			fullscreen(false)
	{}

	VideoSettings::~VideoSettings()
	{}

	bool VideoSettings::loadFromFile(std::string filepath)
	{
		return false;
	}
}