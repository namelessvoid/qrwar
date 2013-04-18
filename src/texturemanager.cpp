#include <iostream>

#include "texturemanager.hpp"

namespace qrw
{
	TextureManager* TextureManager::texturemanager = NULL;

	TextureManager::TextureManager()
	{
	}

	TextureManager::~TextureManager()
	{
		std::map<std::string, sf::Texture*>::iterator iter;
		for(iter = textures.begin(); iter != textures.end(); ++iter)
		{
			delete iter->second;
			textures.erase(iter);
		}
	}

	TextureManager& TextureManager::getInstance()
	{
		if(texturemanager == NULL)
			texturemanager = new TextureManager();
		return *texturemanager;
	}

	bool TextureManager::loadTexture(const std::string texname,
		const std::string filepath)
	{
		// Texture already exists
		if(textures.find(texname) != textures.end())
			return true;

		sf::Texture* texture = new sf::Texture();
		// if load successful
		if(texture->loadFromFile(filepath))
		{
			textures[texname] = texture;
			return true;
		}
		else
		{
			delete texture;
			std::cerr << "Failed to load texture '" << texname << "' from '"
				<< filepath << "'!\n";
			return false;
		}
	}

	const sf::Texture* TextureManager::getTexture(const std::string texname)
	{
		// Texture with given name does not exist
		if(textures.find(texname) == textures.end())
			return NULL;
		return textures[texname];
	}
}