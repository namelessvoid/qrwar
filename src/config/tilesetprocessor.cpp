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

	TilesetProcessor::~TilesetProcessor()
	{
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

		tinyxml2::XMLElement* tilesetroot = doc.FirstChildElement("tileset");
		if(tilesetroot == NULL)
		{
			std::cout << getParsingErrorMsg() << "no child element 'tileset'" << std::endl;
			return -1;
		}

		// Get the texture file path
		tinyxml2::XMLElement* tilesetchild = tilesetroot->FirstChildElement("file");
		if(tilesetchild == NULL)
		{
			std::cout << getParsingErrorMsg() << "no child element 'file'" << std::endl;
			return -1;
		}
		std::string texturefilepath = tilesetchild->Attribute("href");

		// Parse tiles
		tilesetchild = tilesetroot->FirstChildElement("tiles");
		if(tilesetchild == NULL)
		{
			std::cout << getParsingErrorMsg() << "no child element 'tiles'" << std::endl;
			return -1;
		}

		for(tilesetchild = tilesetchild->FirstChildElement("tile");
			tilesetchild != NULL; tilesetchild = tilesetchild->NextSiblingElement())
		{
			if(processTile(tilesetchild, texturefilepath) == false)
			{
				std::cout << getParsingErrorMsg() << "failed parsing tile.\n";
				return -1;
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
