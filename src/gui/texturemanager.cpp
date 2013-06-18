#include <iostream>

#include "gui/texturemanager.hpp"

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

	TextureManager* TextureManager::getInstance()
	{
		if(texturemanager == NULL)
			texturemanager = new TextureManager();
		return texturemanager;
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

	bool TextureManager::unloadTexture(const std::string texname)
	{
		std::map<std::string, sf::Texture*>::iterator texiter
			= textures.find(texname);
		if(texiter == textures.end())
		{
			std::cerr << "TextureManager::unloadTexture failed: no such texture: "
				<< texname << "!\n";
			return 1;
		}

		sf::Texture* texture = texiter->second;
		delete texture;
		textures.erase(texiter);

		return 0;
	}

	const sf::Texture* TextureManager::getTexture(const std::string texname)
	{
		// Texture with given name does not exist
		if(textures.find(texname) == textures.end())
			return NULL;
		return textures[texname];
	}
}