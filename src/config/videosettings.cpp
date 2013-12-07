#include "config/videosettings.hpp"

#include <iostream>
#include <tinyxml2.h>

namespace qrw
{
	VideoSettings::VideoSettings()
		:	resolutionX(800),
			resolutionY(600),
			fullscreen(false)
	{
		setParsingErrorMsg("VideoSettings parsing error: ");
	}

	VideoSettings::~VideoSettings()
	{}

	void VideoSettings::setResolutionX(int resolutionX)
	{
		this->resolutionX = resolutionX;
	}

	int VideoSettings::getResolutionX()
	{
		return resolutionX;
	}


	void VideoSettings::setResolutionY(int resolutionY)
	{
		this->resolutionY = resolutionY;
	}

	int VideoSettings::getResolutionY()
	{
		return resolutionY;
	}

	void VideoSettings::setFullscreen(bool fullscreen)
	{
		this->fullscreen = fullscreen;
	}

	bool VideoSettings::getFullscreen()
	{
		return fullscreen;
	}

	bool VideoSettings::loadFromFile(std::string filepath)
	{
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLError error = tinyxml2::XML_NO_ERROR;
		tinyxml2::XMLElement* videoroot = NULL;
		tinyxml2::XMLElement* element = NULL;

		int intvaluestorage = 0;
		bool boolvaluestorage = false;

		if(doc.LoadFile(filepath.c_str()) != 0)
		{
			printDocumentLoadError(filepath);
			return false;
		}

		videoroot = doc.FirstChildElement("settings");
		if(!videoroot)
		{
			printTagMissingError("settings");
			return false;
		}

		videoroot = videoroot->FirstChildElement("video");
		if(!videoroot)
		{
			printTagMissingError("video");
			return false;
		}

		// Parse fullscreen
		element = videoroot->FirstChildElement("fullscreen");
		if(!element)
		{
			printTagMissingError("fullscreen");
			return false;
		}

		error = element->QueryBoolAttribute("enabled", &boolvaluestorage);
		if(error != tinyxml2::XML_NO_ERROR)
		{
			printAttributeError(error, "height");
			return false;
		}
		setFullscreen(boolvaluestorage);

		// Parse resolution
		// width
		element = videoroot->FirstChildElement("resolution");
		if(!element)
		{
			printTagMissingError("resolution");
			return false;
		}

		error = element->QueryIntAttribute("w", &intvaluestorage);
		if(error != tinyxml2::XML_NO_ERROR)
		{
			printAttributeError(error, "w");
			return false;
		}
		setResolutionX(intvaluestorage);
		
		error = element->QueryIntAttribute("h", &intvaluestorage);
		if(error != tinyxml2::XML_NO_ERROR)
		{
			printAttributeError(error, "h");
			return false;
		}
		setResolutionY(intvaluestorage);

		return false;
	}
}