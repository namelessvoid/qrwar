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
		if(filepath == "")
			filepath = defaultsettingspath;

		if (!AudioSettings::loadFromFile(filepath))
		{
			return false;
		}

		if (!VideoSettings::loadFromFile(filepath))
		{
			return false;
		}
		return true;
	}

	int Settings::saveToFile(std::string filepath)
	{
		if(filepath == "")
			filepath = defaultsettingspath;

		tinyxml2::XMLDocument doc;
		tinyxml2::XMLElement* rootelement = doc.NewElement("settings");
		doc.InsertEndChild(rootelement);

		tinyxml2::XMLElement* videoelement = VideoSettings::toTinyxml2Element(&doc);
		rootelement->InsertEndChild(videoelement);

		return doc.SaveFile(filepath.c_str());
	}
}
