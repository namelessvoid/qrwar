#include "config/tilesetprocessor.hpp"

#include <iostream>

#include "gui/texturemanager.hpp"

namespace qrw
{
	TilesetProcessor::TilesetProcessor()
	{
		texturemanager = TextureManager::getInstance();
		setParsingErrorMsg("TilesetProcessor parsing error: ");
	}


	int TilesetProcessor::loadTileset(std::string filepath)
	{
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLError error = doc.LoadFile(filepath.c_str());
		if(error != tinyxml2::XML_SUCCESS)
		{
			std::cout << "Error parsing tileset '" << filepath << "';\n";
			std::cout << "   " << doc.ErrorStr() << "'\n";
			return -1;
		}

		tinyxml2::XMLElement* tileset = doc.FirstChildElement("tileset");
		if(tileset == nullptr)
		{
			std::cout << getParsingErrorMsg() << "no child element 'tileset'" << std::endl;
			return -1;
		}

		tinyxml2::XMLElement* file = tileset->FirstChildElement("file");
		if(file == nullptr)
		{
			std::cout << getParsingErrorMsg() << "no child element 'file' in 'tileset'" << std::endl;
			return -1;
		}

		for(file = tileset->FirstChildElement("file");
			file != nullptr;
			file = file->NextSiblingElement())
		{
			std::string texturefilepath = file->Attribute("path");

			tinyxml2::XMLElement* tile;
			for (tile = file->FirstChildElement("tile");
				 tile != nullptr;
				 tile = tile->NextSiblingElement())
			{
				if (!processTile(tile, texturefilepath))
				{
					std::cout << getParsingErrorMsg() << "failed parsing tile.\n";
					return -1;
				}
			}
		}

		return 0;
	}

	bool TilesetProcessor::processTile(tinyxml2::XMLElement* xmlelement,
		std::string texturefilepath)
	{
		sf::IntRect area;
		tinyxml2::XMLError error = tinyxml2::XML_SUCCESS;
		error = xmlelement->QueryIntAttribute("x", &area.left);
		printAttributeError(error, "x");
		if(error) return false;

		error = xmlelement->QueryIntAttribute("y", &area.top);
		printAttributeError(error, "y");
		if(error) return false;

		error = xmlelement->QueryIntAttribute("width", &area.width);
		printAttributeError(error, "width");
		if(error) return false;

		error = xmlelement->QueryIntAttribute("height", &area.height);
		printAttributeError(error, "height");
		if(error) return false;

		const char* tilename = xmlelement->Attribute("name");
		if(tilename == NULL)
		{
			std::cerr << getParsingErrorMsg() << "attribute 'name' in 'tile' does not exist\n";
			return false;
		}

		// Replace texture in texturemanager
		texturemanager->unloadTexture(tilename);
		texturemanager->loadTexture(tilename, texturefilepath, area);
		return true;
	}
}
