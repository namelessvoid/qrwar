#include "config/tilesetprocessor.hpp"

#include <iostream>

#include "gui/texturemanager.hpp"

#define PARSING_ERROR "TilesetProcessor parsing error: "

namespace qrw
{
	TilesetProcessor::TilesetProcessor()
	{
		texturemanager = TextureManager::getInstance();
	}

	TilesetProcessor::~TilesetProcessor()
	{
	}

	int TilesetProcessor::loadTileset(std::string filepath)
	{
		tinyxml2::XMLDocument doc;
		int error = doc.LoadFile(filepath.c_str());
		if(error != 0)
		{
			std::cout << "No such tileset file: '" << filepath << "'\n";
			return -1;
		}

		tinyxml2::XMLElement* tilesetroot = doc.FirstChildElement("tileset");
		if(tilesetroot == NULL)
		{
			std::cout << PARSING_ERROR << "no child element 'tileset'" << std::endl;
			return -1;
		}

		// Get the texture file path
		tinyxml2::XMLElement* tilesetchild = tilesetroot->FirstChildElement("file");
		if(tilesetchild == NULL)
		{
			std::cout << PARSING_ERROR << "no child element 'file'" << std::endl;
			return -1;
		}
		std::string texturefilepath = tilesetchild->Attribute("href");

		// Parse tiles
		tilesetchild = tilesetroot->FirstChildElement("tiles");
		if(tilesetchild == NULL)
		{
			std::cout << PARSING_ERROR << "no child element 'tiles'" << std::endl;
			return -1;
		}

		for(tilesetchild = tilesetchild->FirstChildElement("tile");
			tilesetchild != NULL; tilesetchild = tilesetchild->NextSiblingElement())
		{
			if(processTile(tilesetchild, texturefilepath) == false)
			{
				std::cout << PARSING_ERROR << "failed parsing tile.\n";
				return -1;
			}
		}
		return 0;
	}

	bool TilesetProcessor::processTile(tinyxml2::XMLElement* xmlelement,
		std::string texturefilepath)
	{
		sf::IntRect area;
		int error = 0;
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
			std::cerr << PARSING_ERROR << "attribute 'name' in 'tile' does not exist\n";
			return false;
		}

		// Replace texture in texturemanager
		texturemanager->unloadTexture(tilename);
		texturemanager->loadTexture(tilename, texturefilepath, area);
		return true;
	}

	void TilesetProcessor::printAttributeError(int error, std::string attributename)
	{
		if(error == tinyxml2::XML_NO_ATTRIBUTE)
		{
			std::cerr << PARSING_ERROR << "attribute '" << attributename
				<< "'' in 'tile' does not exist!\n";
		}
		else if(error == tinyxml2::XML_WRONG_ATTRIBUTE_TYPE)
		{
			std::cerr << PARSING_ERROR << "attribute '" << attributename
				<< "' in 'tile' has wrong type!\n";
		}
	}
}
