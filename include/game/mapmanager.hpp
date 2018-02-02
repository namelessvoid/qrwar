#ifndef QRW_MAPMANAGER_HPP
#define QRW_MAPMANAGER_HPP

#include <experimental/filesystem>
#include <string>

namespace qrw {

class Board;

class MapManager
{
public:
    ~MapManager();

    static MapManager* get();

    Board* loadMap(const std::string& mapName);

    bool doesMapExist(const std::string& mapName);

    void saveMap(const std::string& mapName, const Board& board);

	std::vector<std::string> getMapList() const;

private:
    MapManager();

	std::string mapNameToPath(const std::string& mapName) const;
	std::string pathToMapName(const std::experimental::filesystem::path& fileName) const;

	std::experimental::filesystem::path getUserMapDir() const;

    static MapManager* instance_;

    MapManager(const MapManager& rhs) = delete;
    MapManager& operator=(const MapManager& rhs) = delete;
};


} // namespace qrw

#endif // QRW_MAPMANAGER_HPP
