#ifndef QRW_MAPMANAGER_HPP
#define QRW_MAPMANAGER_HPP

#include <experimental/filesystem>
#include <string>
#include <vector>

namespace qrw {

class Board;
class DeploymentZone;

class MapManager
{
public:
    enum class LoadErrors
    {
        SUCCESS,
        MAP_NOT_FOUND,
        MISSING_BOARD,
        MULTIPLE_BOARDS,
        MISSING_DEPLOYMENT_ZONE
    };

    ~MapManager();

    static MapManager* get();

    bool doesMapExist(const std::string& mapName);

    LoadErrors loadMap(
        const std::string& mapName,
        Board*& board,
        std::vector<DeploymentZone*>& deploymentZones);

    void saveMap(
        const std::string& mapName,
        const Board& board,
        const std::vector<DeploymentZone*>& deploymentZones);

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
