#include "config/settings.hpp"

#include <iostream>

namespace qrw
{
	Settings* Settings::instance = NULL;

	Settings::Settings()
	{}

	Settings::~Settings()
	{}

	Settings* Settings::getInstance()
	{
		if(instance == NULL)
			instance = new Settings();
		return instance;
	}

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