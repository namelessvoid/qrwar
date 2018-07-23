#ifndef QRW_MAPMANAGER_HPP
#define QRW_MAPMANAGER_HPP

#include <experimental/filesystem>
#include <string>
#include <vector>

#include "game/skirmish/mapvalidator.hpp"
#include "meta/metamanager.hpp"

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
        MAP_VALIDATION_FAILED
    };

	MapManager(MetaManager& metaManager);
    virtual ~MapManager();

    virtual bool doesMapExist(const std::string& mapName);

    virtual LoadErrors loadMap(
        const std::string& mapName,
        Board*& board,
        std::vector<DeploymentZone*>& deploymentZones);

    void saveMap(
        const std::string& mapName,
        const Board& board,
        const std::vector<DeploymentZone*>& deploymentZones);

	virtual std::vector<std::string> getMapList() const;

private:
	std::string mapNameToPath(const std::string& mapName) const;
	std::string pathToMapName(const std::experimental::filesystem::path& fileName) const;

	std::experimental::filesystem::path getUserMapDir() const;

	MetaManager& metaManager_;

    std::unique_ptr<MapValidator> mapValidator_;

    MapManager(const MapManager& rhs) = delete;
    MapManager& operator=(const MapManager& rhs) = delete;
};


} // namespace qrw

#endif // QRW_MAPMANAGER_HPP
