#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <game/meta/boardmetaclass.hpp>
#include <game/meta/terrainmetaclass.hpp>
#include <engine/terrain.hpp>
#include <game/meta/deploymentzonemetaclass.hpp>
#include <game/deploymentzone.hpp>
#include <game/meta/coordinatemetaclass.hpp>

#include "game/states/skirmishpreparationstate.hpp"
#include "game/states/deploystate.hpp"

#include "game/skirmish/mapmanager.hpp"

#include "engine/board.hpp"
#include "game/deploymentzone.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::ElementsAreArray;
using ::testing::ElementsAre;

class MapManagerMock : public qrw::MapManager
{
public:
	MapManagerMock(qrw::MetaManager& metaManager) : MapManager(metaManager) {}

	MOCK_METHOD3(loadMap, qrw::MapManager::LoadErrors(const std::string& mapName, qrw::Board*& board, std::vector<qrw::DeploymentZone*>& deploymentZones));
	MOCK_CONST_METHOD0(getMapList, std::vector<std::string>());
};

ACTION_P2(LoadMapStub, board, deploymentZones)
{
	arg1 = board;
	arg2 = deploymentZones;
	return qrw::MapManager::LoadErrors::SUCCESS;
}

TEST(DeployState_Init, Then_game_objects_are_added_to_scene)
{
	// Arrange
	qrw::MetaManager metaManager;
	metaManager.registerMetaClass<qrw::BoardMetaClass>(qrw::Board::typeName);
	metaManager.registerMetaClass<qrw::TerrainMetaClass>(qrw::Terrain::typeName);
	metaManager.registerMetaClass<qrw::DeploymentZoneMetaClass>(qrw::DeploymentZone::typeName);
	metaManager.registerMetaClass<qrw::CoordinateMetaClass>(qrw::Coordinates::typeName);

	auto board = new qrw::Board();
	auto terrain1 = new qrw::Terrain();
	auto terrain2 = new qrw::Terrain();
	board->setTerrain({0, 0}, terrain1);
	board->setTerrain({1, 0}, terrain2);
	auto deploymentZone1 = new qrw::DeploymentZone();
	auto deploymentZone2 = new qrw::DeploymentZone();
	std::vector<qrw::DeploymentZone*> deploymentZones { deploymentZone1, deploymentZone2 };

	// Assert Mocks
	MapManagerMock mapManager(metaManager);
	EXPECT_CALL(mapManager, getMapList())
		.WillOnce(Return(std::vector<std::string>{"HelloMap"}));
	EXPECT_CALL(mapManager, loadMap("HelloMap", _, _))
		.WillOnce(LoadMapStub(board, deploymentZones));

	sf::RenderWindow renderWindow;

	auto deployState = new qrw::DeployState(&renderWindow, mapManager);

	qrw::SkirmishPreparationState skirmishPreparationState(&renderWindow, mapManager);

	// Act
	deployState->init(&skirmishPreparationState);

	// Assert
	EXPECT_EQ(qrw::g_scene.findSingleGameObject<qrw::Board>(), board);
	EXPECT_THAT(qrw::g_scene.findGameObjects<qrw::DeploymentZone>(), ElementsAreArray(deploymentZones.data(), 2));
	EXPECT_THAT(qrw::g_scene.findGameObjects<qrw::Terrain>(), ElementsAre(terrain1, terrain2));

	// Cleanup
	delete deployState;
	qrw::g_scene.reset();
	qrw::g_scene.update(0);
}