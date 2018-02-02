#include "game/mapmanager.hpp"

#include <cstdlib>
#include <fstream>
#include <regex>

#include "meta/metamanager.hpp"

#include "engine/board.hpp"

namespace fs = std::experimental::filesystem;

namespace qrw
{

MapManager* MapManager::instance_ = nullptr;

MapManager::MapManager()
{
}

MapManager::~MapManager()
{
}

MapManager* MapManager::get()
{
	if(instance_ == nullptr)
		instance_ = new MapManager();
	return instance_;
}

Board* MapManager::loadMap(const std::string& mapName)
{
	assert(doesMapExist(mapName));

	const MetaClass* boardMetaClass = MetaManager::getMetaClassFor<Board>();

	std::vector<YAML::Node> documents = YAML::LoadAllFromFile(getUserMapDir() / mapNameToPath(mapName));

	Board* board = static_cast<Board*>(boardMetaClass->deserialize(documents.at(1)[0]["qrw::Board"]));

	return board;
}

bool MapManager::doesMapExist(const std::string& mapName)
{
	fs::path mapFilePath = getUserMapDir() / mapNameToPath(mapName);

	return fs::exists(mapFilePath);
}

void MapManager::saveMap(const std::string& mapName, const Board& board)
{
	const MetaClass* boardMetaClass = MetaManager::getMetaClassFor<Board>();
	const std::string fileName = mapNameToPath(mapName);

	YAML::Emitter yaml;
	yaml << YAML::BeginDoc
		 << YAML::Comment("Description")
		 << YAML::BeginMap
			<< YAML::Key << "name" << YAML::Value << mapName
			<< YAML::Key << "short-description" << YAML::Value << "Here goes the short description"
			<< YAML::Key << "player-count" << YAML::Value << 2
		 << YAML::EndMap;

	yaml << YAML::BeginDoc
		 << YAML::BeginSeq;
			boardMetaClass->serialize(&board, yaml);
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
