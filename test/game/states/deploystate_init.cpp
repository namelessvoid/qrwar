#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "game/skirmish/meta/boardmetaclass.hpp"
#include "game/skirmish/meta/terrainmetaclass.hpp"
#include "game/skirmish/meta/deploymentzonemetaclass.hpp"
#include "game/skirmish/meta/coordinatemetaclass.hpp"
#include "engine/terrain.hpp"
#include "game/skirmish/wall.hpp"
#include "game/deploymentzone.hpp"

#include "game/states/skirmishpreparationstate.hpp"
#include "game/states/deploystate.hpp"

#include "game/skirmish/mapmanager.hpp"

#include "engine/board.hpp"
#include "game/deploymentzone.hpp"

#include "__mocks__/game/skirmish/mapmanagermock.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::ElementsAreArray;
using ::testing::Contains;

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
	auto wall1 = new qrw::Wall();
	auto wall2 = new qrw::Wall();
	board->setStructure({2, 0}, wall2);
	board->setStructure({3, 0}, wall1);
	auto deploymentZone1 = new qrw::DeploymentZone();
	auto deploymentZone2 = new qrw::DeploymentZone();
	std::vector<qrw::DeploymentZone*> deploymentZones { deploymentZone1, deploymentZone2 };

	// Assert Mocks
	MapManagerMock mapManager(metaManager);
	qrw::MapDto mapDto;
	mapDto.board = board;
	mapDto.deploymentZones = deploymentZones;
	EXPECT_CALL(mapManager, getMapList())
		.WillOnce(Return(std::vector<std::string>{"HelloMap"}));
	EXPECT_CALL(mapManager, loadMap("HelloMap", _))
		.WillOnce(MapManagerMock_LoadMapAction(qrw::MapManager::LoadErrors::SUCCESS, mapDto));

	sf::RenderWindow renderWindow;
	qrw::SkirmishGuiFactory skirmishGuiFactory(mapManager);

	auto deployState = new qrw::DeployState(&renderWindow, mapManager);

	qrw::SkirmishPreparationState skirmishPreparationState(&renderWindow, mapManager, skirmishGuiFactory);

	// Act
	deployState->init(&skirmishPreparationState);

	// Assert
	EXPECT_EQ(qrw::g_scene.findSingleGameObject<qrw::Board>(), board);
	EXPECT_THAT(qrw::g_scene.findGameObjects<qrw::DeploymentZone>(), ElementsAreArray(deploymentZones.data(), 2));

	std::set<qrw::GameObject*> terrainsInScene = qrw::g_scene.findGameObjects<qrw::Terrain>();
	EXPECT_EQ(terrainsInScene.size(), 2);
	EXPECT_THAT(terrainsInScene, Contains(terrain1));
	EXPECT_THAT(terrainsInScene, Contains(terrain2));

	std::set<qrw::GameObject*> structuresInScene = qrw::g_scene.findGameObjects<qrw::Wall>();
	EXPECT_EQ(structuresInScene.size(), 2);
	EXPECT_THAT(structuresInScene, Contains(wall1));
	EXPECT_THAT(structuresInScene, Contains(wall2));

	// Cleanup
	delete deployState;
	qrw::g_scene.reset();
	qrw::g_scene.update(0);
}