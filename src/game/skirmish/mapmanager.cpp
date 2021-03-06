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
#include "game/skirmish/boardbackgroundcomponent.hpp"
#include "game/skirmish/isometricconversion.hpp"
#include "engine/terrain.hpp"
#include "game/skirmish/minimapgenerator.hpp"

namespace fs = std::experimental::filesystem;

namespace qrw
{

MapManager::MapManager(MetaManager& metaManager)
  : metaManager_(metaManager),
	mapValidator_(new MapValidator())
{
	logger_ = std::make_unique<Logger>();
	logger_->setPrefix("MapManager");
}

void MapManager::ensureUserMapDir()
{
	if(!fs::exists(getUserMapDir()))
		fs::create_directories(getUserMapDir());
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

	std::vector<YAML::Node> documents = YAML::LoadAllFromFile((getUserMapDir() / convertMapNameToPath(mapName, ".map")).string());
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
			logger_->logError("Found unsupported game object in map '"
				  + mapName + "': "
				  + node[MetaClass::TYPE_NAME_YAML_KEY].as<std::string>());
		}
	}

	error = LoadErrors::SUCCESS;
	return mapDto;
}

bool MapManager::doesMapExist(const std::string& mapName)
{
	fs::path mapFilePath = getUserMapDir() / convertMapNameToPath(mapName, ".map");

	return fs::exists(mapFilePath);
}

void MapManager::saveMap(
	const std::string& mapName,
	const MapDto& dto)
{
	const std::string fileName = convertMapNameToPath(mapName, ".map");

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

	for(auto& p : fs::directory_iterator(getUserMapDir()))
	{
		if(p.path().extension().compare(".map") == 0)
			mapNames.push_back(convertPathToMapName(p));
	}

	return mapNames;
}

std::string MapManager::convertMapNameToPath(const std::string& mapName, const std::string& extension) const
{
	std::regex whitespaceMatcher("\\s+");
	return std::regex_replace(mapName, whitespaceMatcher, "-") += extension;
}

std::string MapManager::convertPathToMapName(const fs::path& filePath) const
{
	std::regex dashMatcher("-");
	return std::regex_replace(filePath.stem().string(), dashMatcher, " ");
}

void MapManager::createAndSaveMapPreview(const std::string& mapName, const MapDto& dto)
{
	auto image = std::unique_ptr<sf::Image>(generateMiniMap(dto));
	image->saveToFile((getUserMapDir() / convertMapNameToPath(mapName, ".png")).string());
}

sf::Texture* MapManager::loadMapPreview(const std::string& mapName)
{
	sf::Texture* image = new sf::Texture();
	fs::path previewPath = getUserMapDir() / (convertMapNameToPath(mapName, ".png"));
	if(!image->loadFromFile(previewPath.string()))
	{
		logger_->logError("Failed to load map preview from '" + previewPath.string() + "'");
	}

	return image;
}

fs::path MapManager::getUserMapDir() const
{
	return std::string(getenv("HOME")) + "/.qrw/maps";
}

} // namespace qrw
