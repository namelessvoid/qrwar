#include <iostream>

#include "gui/imagemanager.hpp"

namespace qrw
{
	ImageManager* ImageManager::imagemanager = NULL;


	ImageManager::ImageManager()
	{
	}

	ImageManager::~ImageManager()
	{
		std::map<std::string, sf::Image*>::iterator iter;
		for(iter = images.begin(); iter != images.end(); ++iter)
		{
			delete iter->second;
			images.erase(iter);
		}
		imagemanager = NULL;
	}

	ImageManager* ImageManager::getInstance()
	{
		if(imagemanager == false)
			imagemanager = new ImageManager();
		return imagemanager;
	}

	bool ImageManager::loadImage(const std::string imgname,
		const std::string filepath)
	{
		// Image already exists
		if(images.find(imgname) != images.end())
			return true;

		sf::Image* img = new sf::Image();
		// if load successful
		if(img->loadFromFile(filepath))
		{
			images[imgname] = img;
			return true;
		}
		else
		{
			delete img;
			std::cerr << "Failed to load img '" << imgname << "' from '"
				<< filepath << "'!\n";
			return false;
		}
	}

	const sf::Image* ImageManager::getImage(const std::string imgname)
	{
		// Image with given name does not exist
		if(images.find(imgname) == images.end())
			return NULL;
		return images[imgname];
	}
}