#ifndef QRW_MAPMANAGER_HPP
#define QRW_MAPMANAGER_HPP

#include <experimental/filesystem>
#include <string>
#include <vector>

#include "game/skirmish/mapvalidator.hpp"
#include "game/skirmish/mapdto.hpp"
#include "meta/metamanager.hpp"

#include "core/logger.hpp"

namespace sf {
class Texture;
}

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

	explicit MapManager(MetaManager& metaManager);
    virtual ~MapManager() = default;

	MapManager(const MapManager& rhs) = delete;
	MapManager& operator=(const MapManager& rhs) = delete;

    virtual bool doesMapExist(const std::string& mapName);

    virtual MapDto loadMap(
		const std::string& mapName,
		LoadErrors& error);

    sf::Texture* loadMapPreview(const std::string& mapName);

    void saveMap(
        const std::string& mapName,
        const MapDto& dto);

	virtual std::vector<std::string> getMapList() const;

private:
	std::string convertMapNameToPath(const std::string& mapName, const std::string& extension) const;
	std::string convertPathToMapName(const std::experimental::filesystem::path& fileName) const;

	void createAndSaveMapPreview(const std::string& mapName, const MapDto& dto);

	std::experimental::filesystem::path getUserMapDir() const;

	MetaManager& metaManager_;
    std::unique_ptr<MapValidator> mapValidator_;
    std::unique_ptr<Logger> logger_;
};

} // namespace qrw

#endif // QRW_MAPMANAGER_HPP
