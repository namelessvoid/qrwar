#include <iostream>

#include "gui/texturemanager.hpp"

namespace qrw
{
	TextureManager* TextureManager::texturemanager = NULL;

	TextureManager::TextureManager()
	{
		sf::Image textureimage;
		textureimage.create(64, 64, sf::Color(255, 0, 0));

		sf::Color col1(254, 254, 234);
		sf::Color col2(0, 72, 180);

		for(int i = 0; i < 64; ++i)
		{
			for(int j = i * 0.5; j < 64 - (i * 0.5); ++j) {
				textureimage.setPixel(i, j, col1);
			}
		}

		for(int i = 0; i < 64; ++i) {
			textureimage.setPixel(63, i, col2);
			textureimage.setPixel(i, 63, col2);
		}

		fallbacktexture.loadFromImage(textureimage);
	}

	TextureManager::~TextureManager()
	{
		std::map<std::string, sf::Texture*>::iterator iter;
		for(iter = textures.begin(); iter != textures.end(); ++iter)
			delete iter->second;
	}

	TextureManager* TextureManager::getInstance()
	{
		if(texturemanager == NULL)
			texturemanager = new TextureManager();
		return texturemanager;
	}

	bool TextureManager::loadTexture(const std::string texname,
		const std::string filepath, sf::IntRect area)
	{
		// Texture already exists
		if(textures.find(texname) != textures.end())
			return true;

		sf::Texture* texture = new sf::Texture();
		texture->setRepeated(true);
		// if load successful
		if(texture->loadFromFile(filepath, area))
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

	void TextureManager::unloadTexture(const std::string texname)
	{
		std::map<std::string, sf::Texture*>::iterator texiter
			= textures.find(texname);
		if(texiter == textures.end())
			return;

		sf::Texture* texture = texiter->second;
		delete texture;
		textures.erase(texiter);
	}

	const sf::Texture* TextureManager::getTexture(const std::string texname)
	{
		// Texture with given name does not exist
		if(textures.find(texname) == textures.end())
			return getFallbackTexture();
		return textures[texname];
	}

	const sf::Texture* TextureManager::getFallbackTexture()
	{
		return &fallbacktexture;
	}
}
