#include "game/skirmish/mapmanager.hpp"

#include <cstdlib>
#include <fstream>
#include <regex>

#include "meta/metamanager.hpp"

#include "engine/board.hpp"
#include "game/deploymentzone.hpp"

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

	const MetaClass* boardMetaClass = metaManager_.getMetaClassFor<Board>();
	const MetaClass* deploymentZoneMetaClass = metaManager_.getMetaClassFor<DeploymentZone>();

	std::vector<YAML::Node> documents = YAML::LoadAllFromFile(getUserMapDir() / mapNameToPath(mapName));
	if(!mapValidator_->validate(documents))
	{
		error = LoadErrors::MAP_VALIDATION_FAILED;
		return mapDto;
	}

	YAML::Node gameObjectsNode = documents.at(1);

	mapDto.board = new Board();

	for(auto node : gameObjectsNode)
	{
		const SID nodeType(node["type"].as<std::string>());
		if(nodeType == DeploymentZone::typeName)
		{
			DeploymentZone* zone = new DeploymentZone();
			deploymentZoneMetaClass->deserialize(zone, node);
			mapDto.deploymentZones.push_back(zone);
		}
		else if(nodeType == Board::typeName)
		{
			boardMetaClass->deserialize(mapDto.board, node);
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
	const MetaClass* boardMetaClass = metaManager_.getMetaClassFor<Board>();
	const MetaClass* deploymentZoneMetaClass = metaManager_.getMetaClassFor<DeploymentZone>();
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
			boardMetaClass->serialize(dto.board, yaml);
			for(auto& zone : dto.deploymentZones)
				deploymentZoneMetaClass->serialize(zone, yaml);
	yaml << YAML::EndSeq;

	std::ofstream mapFile;
	fs::path userMapDir = getUserMapDir();

	if(!fs::exists(userMapDir))
		fs::create_directories(userMapDir);

	mapFile.open(userMapDir / fileName, std::ofstream::out | std::ofstream::trunc);
	mapFile << yaml.c_str() << std::endl;
	mapFile.close();
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

fs::path MapManager::getUserMapDir() const
{
	return std::string(getenv("HOME")) + "/.qrw/maps";
}

} // namespace qrw
