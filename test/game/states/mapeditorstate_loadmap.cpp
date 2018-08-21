#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "game/states/mapeditorstate.hpp"

#include "game/deploymentzone.hpp"
#include "engine/terrain.hpp"
#include "game/skirmish/structure.hpp"

#include "__mocks__/game/skirmish/gui/skirmishguifactorymock.hpp"
#include "__mocks__/game/skirmish/mapmanagermock.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::ElementsAreArray;
using ::testing::ElementsAre;
using ::testing::Contains;

namespace MapEditorState_LoadMap
{

TEST(MapEditorState_LoadMap, Then_only_loaded_game_objects_are_in_scene)
{
	qrw::g_scene.reset();
	qrw::g_scene.update(0);

	// Arrange
	auto mapEditorToolBar = new qrw::MapEditorToolBar(0, 0);

	SkirmishGuiFactoryMock guiFactory;
	EXPECT_CALL(guiFactory, createMapEditorToolBar(_, _))
			.WillOnce(Return(mapEditorToolBar));

	sf::RenderWindow renderWindow;
	qrw::MetaManager metaManager;
	MapManagerMock mapManager(metaManager);

	auto board = new qrw::Board();
	auto terrain1 = new qrw::Terrain();
	auto terrain2 = new qrw::Terrain();
	board->setTerrain({0, 0}, terrain1);
	board->setTerrain({1, 0}, terrain2);
	auto structure1 = new qrw::Structure();
	auto structure2 = new qrw::Structure();
	board->setStructure({2, 0}, structure1);
	board->setStructure({3, 0}, structure2);
	auto deploymentZone1 = new qrw::DeploymentZone();
	auto deploymentZone2 = new qrw::DeploymentZone();
	std::vector<qrw::DeploymentZone*> deploymentZones{deploymentZone1, deploymentZone2};

	qrw::MapDto mapDto;
	mapDto.board = board;
	mapDto.deploymentZones = deploymentZones;

	EXPECT_CALL(mapManager, doesMapExist("TestMap"))
			.WillOnce(Return(true));
	EXPECT_CALL(mapManager, loadMap("TestMap", _))
			.WillOnce(MapManagerMock_LoadMapAction(qrw::MapManager::LoadErrors::SUCCESS, mapDto));

	qrw::MapEditorState mapEditorState(&renderWindow, mapManager, guiFactory);
	mapEditorState.init(nullptr);

	// Act
	mapEditorToolBar->signalLoadClicked.emit("TestMap");
	qrw::g_scene.update(0);

	// Assert
	EXPECT_TRUE(qrw::g_scene.findSingleGameObject<qrw::Board>()!=nullptr);
	EXPECT_THAT(qrw::g_scene.findGameObjects<qrw::DeploymentZone>(), ElementsAreArray(deploymentZones.data(), 2));

	auto terrains = qrw::g_scene.findGameObjects<qrw::Terrain>();
	EXPECT_EQ(terrains.size(), 2);
	EXPECT_THAT(terrains, Contains(terrain1));
	EXPECT_THAT(terrains, Contains(terrain2));

	auto structures = qrw::g_scene.findGameObjects<qrw::Structure>();
	EXPECT_EQ(structures.size(), 2);
	EXPECT_THAT(structures, Contains(structure1));
	EXPECT_THAT(structures, Contains(structure2));

	// Clean Up
	qrw::g_scene.reset();
	qrw::g_scene.update(0);
}

} // namespace MapEditorState_Init