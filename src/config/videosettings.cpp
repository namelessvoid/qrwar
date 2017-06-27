#include "config/videosettings.hpp"

#include <iostream>

namespace qrw
{
	VideoSettings::VideoSettings()
		:	_resolutionX(800),
			_resolutionY(600),
			_fullscreen(false),
			_entitytilesetpath("res/defaulttileset.xml")
	{
		setParsingErrorMsg("VideoSettings parsing error: ");
	}

	VideoSettings::~VideoSettings()
	{}

	void VideoSettings::setResolutionX(int resolutionX)
	{
		this->_resolutionX = resolutionX;
	}

	int VideoSettings::getResolutionX()
	{
		return _resolutionX;
	}


	void VideoSettings::setResolutionY(int resolutionY)
	{
		this->_resolutionY = resolutionY;
	}

	int VideoSettings::getResolutionY()
	{
		return _resolutionY;
	}

	void VideoSettings::setFullscreen(bool fullscreen)
	{
		this->_fullscreen = fullscreen;
	}

	bool VideoSettings::getFullscreen()
	{
		return _fullscreen;
	}

	void VideoSettings::setEntityTilesetPath(std::string entitytilesetpath)
	{
		this->_entitytilesetpath = entitytilesetpath;
	}

	std::string VideoSettings::getEntityTilesetPath()
	{
		return _entitytilesetpath;
	}

	void VideoSettings::setGuiTilesetPath(std::string guitilesetpath)
	{
		this->_guitilesetpath = guitilesetpath;
	}

	std::string VideoSettings::getGuiTilesetPath()
	{
		return _guitilesetpath;
	}

	bool VideoSettings::loadFromFile(std::string filepath)
	{
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLError error = tinyxml2::XML_SUCCESS;
		tinyxml2::XMLElement* videoroot = NULL;
		tinyxml2::XMLElement* element = NULL;

		int intvaluestorage = 0;
		bool boolvaluestorage = false;
		const char* stringvaluestorage = NULL;

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
		if(error != tinyxml2::XML_SUCCESS)
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
		if(error != tinyxml2::XML_SUCCESS)
		{
			printAttributeError(error, "w");
			return false;
		}
		setResolutionX(intvaluestorage);
		
		// height
		error = element->QueryIntAttribute("h", &intvaluestorage);
		if(error != tinyxml2::XML_SUCCESS)
		{
			printAttributeError(error, "h");
			return false;
		}
		setResolutionY(intvaluestorage);

		// Parse entitytileset
		element = videoroot->FirstChildElement("entitytileset");
		if(!element)
		{
			printTagMissingError("entitytileset");
			return false;
		}

		stringvaluestorage = element->Attribute("path");
		if(!stringvaluestorage)
		{
			printAttributeError(tinyxml2::XML_NO_ATTRIBUTE, "path");
			return false;
		}
		setEntityTilesetPath(stringvaluestorage);

		// Parse guitileset
		element = videoroot->FirstChildElement("guitileset");
		if(!element)
		{
			printTagMissingError("guitileset");
			return false;
		}

		stringvaluestorage = element->Attribute("path");
		if(!stringvaluestorage)
		{
			printAttributeError(tinyxml2::XML_NO_ATTRIBUTE, "path");
			return false;
		}
		setGuiTilesetPath(stringvaluestorage);
		return false;
	}

	tinyxml2::XMLElement* VideoSettings::toTinyxml2Element(tinyxml2::XMLDocument* document)
	{
		tinyxml2::XMLElement* rootelement = document->NewElement("video");

		tinyxml2::XMLElement* subelement = document->NewElement("fullscreen");
		subelement->SetAttribute("enabled", getFullscreen());
		rootelement->InsertEndChild(subelement);

		subelement = document->NewElement("resolution");
		subelement->SetAttribute("w", getResolutionX());
		subelement->SetAttribute("h", getResolutionY());
		rootelement->InsertEndChild(subelement);

		subelement = document->NewElement("entitytileset");
		subelement->SetAttribute("path", getEntityTilesetPath().c_str());
		rootelement->InsertEndChild(subelement);

		subelement = document->NewElement("guitileset");
		subelement->SetAttribute("path", getGuiTilesetPath().c_str());
		rootelement->InsertEndChild(subelement);

		return rootelement;
	}
}
