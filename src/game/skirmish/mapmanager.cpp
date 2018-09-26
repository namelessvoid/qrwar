#include "game/skirmish/mapmanager.hpp"

#include <cstdlib>
#include <fstream>
#include <regex>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include "foundation/spritecomponent.hpp"

#include "meta/metamanager.hpp"

#include "engine/board.hpp"
#include "game/constants.hpp"
#include "game/deploymentzone.hpp"
#include "game/skirmish/structure.hpp"
#include "engine/terrain.hpp"

namespace fs = std::experimental::filesystem;

namespace qrw
{

MapManager::MapManager(MetaManager& metaManager)
  : metaManager_(metaManager),
	mapValidator_(new MapValidator())
{
}

MapManager::~MapManager()
{
}

MapDto MapManager::loadMap(
	const std::string& mapName,
	LoadErrors& error)
{
	MapDto mapDto;

	if(!doesMapExist(mapName))
	{
		error = LoadErrors::MAP_NOT_FOUND;
		return mapDto;
	}

	std::vector<YAML::Node> documents = YAML::LoadAllFromFile(getUserMapDir() / mapNameToPath(mapName));
	if(!mapValidator_->validate(documents))
	{
		error = LoadErrors::MAP_VALIDATION_FAILED;
		return mapDto;
	}

	YAML::Node gameObjectsNode = documents.at(1);

	for(auto node : gameObjectsNode)
	{
		auto gameObject = metaManager_.deserialize(node);

		if(auto zone = dynamic_cast<DeploymentZone*>(gameObject))
		{
			mapDto.deploymentZones.push_back(zone);
		}
		else if(auto board = dynamic_cast<Board*>(gameObject))
		{
			mapDto.board = board;
		}
		else
		{
			std::cerr << "Found unsupported game object in map \'"
					<< mapName << "\': "
				  	<< node[MetaClass::TYPE_NAME_YAML_KEY].as<std::string>() << std::endl << std::flush;
		}
	}

	error = LoadErrors::SUCCESS;
	return mapDto;
}

bool MapManager::doesMapExist(const std::string& mapName)
{
	fs::path mapFilePath = getUserMapDir() / mapNameToPath(mapName);

	return fs::exists(mapFilePath);
}

void MapManager::saveMap(
	const std::string& mapName,
	const MapDto& dto)
{
	const std::string fileName = mapNameToPath(mapName);

	YAML::Emitter yaml;
	yaml << YAML::BeginDoc
		 << YAML::Comment("Description")
		 << YAML::BeginMap
			<< YAML::Key << "name" << YAML::Value << mapName
			<< YAML::Key << "short-description" << YAML::Value << "Here goes the short description"
			<< YAML::Key << "playerCount" << YAML::Value << 2
	    << YAML::EndMap;

	yaml << YAML::BeginDoc
		 << YAML::BeginSeq;
			metaManager_.serialize(dto.board, yaml);
			for(auto& zone : dto.deploymentZones)
				metaManager_.serialize(zone, yaml);
	yaml << YAML::EndSeq;

	std::ofstream mapFile;
	fs::path userMapDir = getUserMapDir();

	if(!fs::exists(userMapDir))
		fs::create_directories(userMapDir);

	mapFile.open(userMapDir / fileName, std::ofstream::out | std::ofstream::trunc);
	mapFile << yaml.c_str() << std::endl;
	mapFile.close();

	createAndSaveMapPreview(mapName, dto);
}

std::vector<std::string> MapManager::getMapList() const
{
	std::vector<std::string> mapNames;

	for(auto& p: fs::directory_iterator(getUserMapDir()))
		mapNames.push_back(pathToMapName(p));

	return mapNames;
}

std::string MapManager::mapNameToPath(const std::string& mapName) const
{
	std::regex whitespaceMatcher("\\s+");
	return std::regex_replace(mapName, whitespaceMatcher, "-") += ".map";
}

std::string MapManager::pathToMapName(const fs::path& filePath) const
{
	std::regex dashMatcher("-");
	return std::regex_replace(filePath.stem().string(), dashMatcher, " ");
}

void MapManager::createAndSaveMapPreview(const std::string mapName, const MapDto& dto)
{
	sf::RenderTexture renderTexture;
	renderTexture.create(
			static_cast<unsigned int>(dto.board->getWidth() * SQUARE_DIMENSION),
			static_cast<unsigned int>(dto.board->getHeight() * SQUARE_DIMENSION));
	dto.board->getComponent<SpriteComponent>()->render(renderTexture);
	for(auto& structureIter : dto.board->getStructures())
		structureIter.second->getComponent<SpriteComponent>()->render(renderTexture);
	for(auto& terrainIter : dto.board->getTerrains())
		terrainIter.second->getComponent<SpriteComponent>()->render(renderTexture);
	for(auto& deploymentZone : dto.deploymentZones)
		deploymentZone->render(renderTexture);
	renderTexture.display();
	renderTexture.getTexture().copyToImage().saveToFile(getUserMapDir() / (mapNameToPath(mapName) + ".png"));
}

fs::path MapManager::getUserMapDir() const
{
	return std::string(getenv("HOME")) + "/.qrw/maps";
}

sf::Texture* MapManager::loadMapPreview(const std::string& mapName)
{
	sf::Texture* image = new sf::Texture();
	fs::path previewPath = getUserMapDir() / (mapNameToPath(mapName) + ".png");
	std::cerr << "Loading map preview from " << previewPath << std::endl << std::flush;
	if(!image->loadFromFile(previewPath))
		std::cerr << "Failed to load map preview\n" << std::flush;

	return image;
}

} // namespace qrw
