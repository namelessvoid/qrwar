#include "game/mapmanager.hpp"

#include <experimental/filesystem>
#include <cstdlib>
#include <fstream>

#include "core/stringutils.hpp"

#include "meta/metamanager.hpp"

#include "engine/board.hpp"

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
	const MetaClass* boardMetaClass = MetaManager::getMetaClassFor<Board>();

	Board* board = new Board();

	std::vector<YAML::Node> documents = YAML::LoadAllFromFile(mapNameToFileName(mapName));

	std::cout << documents.at(1)[0]["qrw::Board"] << std::endl << std::flush;
	board->setWidth(documents.at(1)[0]["qrw::Board"]["size"]["width"].as<unsigned int>());
	board->setHeight(documents.at(1)[0]["qrw::Board"]["size"]["height"].as<unsigned int>());

	return board;
}

bool MapManager::doesMapExist(const std::string& mapName)
{
	return true;
}

void MapManager::saveMap(const std::string& mapName, const Board& board)
{
	namespace fs = std::experimental::filesystem;

	const MetaClass* boardMetaClass = MetaManager::getMetaClassFor<Board>();
	const std::string fileName = mapNameToFileName(mapName);

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

	std::cout << yaml.c_str() << std::endl << std::flush;

	std::ofstream mapFile;
	std::string userMapDir = getUserMapDir();

	if(!fs::exists(userMapDir))
		fs::create_directories(userMapDir);

	mapFile.open(userMapDir + "/" + fileName, std::ofstream::out | std::ofstream::trunc);
	mapFile << yaml.c_str() << std::endl;
	mapFile.close();
}

std::string MapManager::mapNameToFileName(std::string mapName)
{
	replaceAll(mapName, " ", "-");
	toLower(mapName);
	mapName += ".map";
	return mapName;
}

std::string MapManager::getUserMapDir()
{
	return std::string(getenv("HOME")) + "/.qrw/maps";
}

} // namespace qrw
