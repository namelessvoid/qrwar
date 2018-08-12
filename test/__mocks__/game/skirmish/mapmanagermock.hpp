#ifndef QRW_TEST_MAPMANAGERMOCK_HPP
#define QRW_TEST_MAPMANAGERMOCK_HPP

#include <gmock/gmock.h>

#include "game/skirmish/mapmanager.hpp"

class MapManagerMock : public qrw::MapManager
{
public:
	MapManagerMock(qrw::MetaManager& metaManager) : qrw::MapManager(metaManager) {}
	MapManagerMock() : qrw::MapManager(metaManager_) {}

	MOCK_METHOD2(loadMap, qrw::MapDto(const std::string& mapName, qrw::MapManager::LoadErrors& error));
	MOCK_METHOD1(doesMapExist, bool(const std::string& mapName));
	MOCK_CONST_METHOD0(getMapList, std::vector<std::string>());

private:
	qrw::MetaManager metaManager_;
};

ACTION_P2(MapManagerMock_LoadMapAction, error, mapDto)
{
	arg1 = qrw::MapManager::LoadErrors::SUCCESS;
	return mapDto;
}

#endif //QRW_TEST_MAPMANAGERMOCK_HPP
