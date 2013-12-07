#include "config/settings.hpp"

#include <iostream>

namespace qrw
{
	Settings::Settings()
	{}

	Settings::~Settings()
	{}

	bool Settings::loadFromFile(std::string filepath)
	{
		if (!AudioSettings::loadFromFile(filepath))
		{
			return false;
		}

		if (!VideoSettings::loadFromFile(filepath))
		{
			return false;
		}
	}
}