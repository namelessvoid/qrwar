#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "game/states/mapeditorstate.hpp"
#include "game/skirmish/gui/mapeditortoolbar.hpp"

#include "engine/terrain.hpp"
#include "game/skirmish/wall.hpp"
#include "game/deploymentzone.hpp"

#include "__mocks__/game/skirmish/mapmanagermock.hpp"
#include "__mocks__/game/skirmish/gui/skirmishguifactorymock.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::Contains;

TEST(MapEditorState_ResizeBoard, Then_terrains_no_longer_on_board_are_removed)
{
	// Arrange
	sf::RenderWindow renderWindow;
	MapManagerMock mapManagerMock;
	SkirmishGuiFactoryMock skirmishGuiFactoryMock;

	qrw::MapEditorToolBar* mapEditorToolBar = new qrw::MapEditorToolBar(10, 10);
	EXPECT_CALL(skirmishGuiFactoryMock, createMapEditorToolBar(_, _))
				.WillOnce(Return(mapEditorToolBar));

	qrw::MapEditorState mapEditorState(&renderWindow, mapManagerMock, skirmishGuiFactoryMock);
	mapEditorState.init(nullptr);

	qrw::Board* board = qrw::g_scene.findSingleGameObject<qrw::Board>();
	qrw::Terrain* terrainWithinBoard1 = qrw::g_scene.spawn<qrw::Terrain>();
	qrw::Terrain* terrainWithinBoard2 = qrw::g_scene.spawn<qrw::Terrain>();
	qrw::Terrain* terrainOutsideWidth = qrw::g_scene.spawn<qrw::Terrain>();
	qrw::Terrain* terrainOutsideHeight = qrw::g_scene.spawn<qrw::Terrain>();

	board->setTerrain({0, 2}, terrainWithinBoard1);
	board->setTerrain({0, 3}, terrainOutsideHeight);

	board->setTerrain({2, 0}, terrainWithinBoard2);
	board->setTerrain({3, 0}, terrainOutsideWidth);

	// Act (mind off-by-one errors)
	mapEditorToolBar->signalBoardWidthChanged.emit(3);
	mapEditorToolBar->signalBoardHeightChanged.emit(3);
	qrw::g_scene.update(0);

	// Assert
	auto terrains = qrw::g_scene.findGameObjects<qrw::Terrain>();
	EXPECT_EQ(terrains.size(), 2);
	EXPECT_THAT(terrains, Contains(terrainWithinBoard1));
	EXPECT_THAT(terrains, Contains(terrainWithinBoard2));

	// Cleanup
	qrw::g_scene.reset();
	qrw::g_scene.update(0);
}

TEST(MapEditorState_ResizeBoard, Then_structures_no_longer_on_board_are_removed)
{
	// Arrange
	sf::RenderWindow renderWindow;
	MapManagerMock mapManagerMock;
	SkirmishGuiFactoryMock skirmishGuiFactoryMock;

	qrw::MapEditorToolBar* mapEditorToolBar = new qrw::MapEditorToolBar(10, 10);
	EXPECT_CALL(skirmishGuiFactoryMock, createMapEditorToolBar(_, _))
			.WillOnce(Return(mapEditorToolBar));

	qrw::MapEditorState mapEditorState(&renderWindow, mapManagerMock, skirmishGuiFactoryMock);
	mapEditorState.init(nullptr);

	qrw::Board* board = qrw::g_scene.findSingleGameObject<qrw::Board>();
	auto structureWithinBoard1 = qrw::g_scene.spawn<qrw::Wall>();
	auto structureWithinBoard2 = qrw::g_scene.spawn<qrw::Wall>();
	auto structureOutsideWidth = qrw::g_scene.spawn<qrw::Wall>();
	auto structureOutsideHeight = qrw::g_scene.spawn<qrw::Wall>();

	board->setStructure({0, 2}, structureWithinBoard1);
	board->setStructure({0, 3}, structureOutsideHeight);

	board->setStructure({2, 0}, structureWithinBoard2);
	board->setStructure({3, 0}, structureOutsideWidth);

	// Act (mind off-by-one errors)
	mapEditorToolBar->signalBoardWidthChanged.emit(3);
	mapEditorToolBar->signalBoardHeightChanged.emit(3);
	qrw::g_scene.update(0);

	// Assert
	auto structures = qrw::g_scene.findGameObjects<qrw::Wall>();
	EXPECT_EQ(structures.size(), 2);
	EXPECT_THAT(structures, Contains(structureWithinBoard1));
	EXPECT_THAT(structures, Contains(structureWithinBoard2));

	// Clean up
	qrw::g_scene.reset();
	qrw::g_scene.update(0);
}

TEST(MapEditorState_ResizeBoard, Then_deployment_zones_are_cropped)
{
	// Arrange
	sf::RenderWindow renderWindow;
	MapManagerMock mapManagerMock;
	SkirmishGuiFactoryMock skirmishGuiFactoryMock;

	qrw::MapEditorToolBar* mapEditorToolBar = new qrw::MapEditorToolBar(10, 10);
	EXPECT_CALL(skirmishGuiFactoryMock, createMapEditorToolBar(_, _))
			.WillOnce(Return(mapEditorToolBar));

	qrw::MapEditorState mapEditorState(&renderWindow, mapManagerMock, skirmishGuiFactoryMock);
	mapEditorState.init(nullptr);

	auto deploymentZones = qrw::g_scene.findGameObjects<qrw::DeploymentZone>();
	qrw::DeploymentZone* zone1 = static_cast<qrw::DeploymentZone*>(*deploymentZones.begin());
	qrw::DeploymentZone* zone2 = static_cast<qrw::DeploymentZone*>(*++deploymentZones.begin());

	zone1->addSquare({0, 2});
	zone1->addSquare({0, 3});
	zone2->addSquare({2, 0});
	zone2->addSquare({3, 0});

	// Act (mind off-by-one errors)
	mapEditorToolBar->signalBoardWidthChanged.emit(3);
	mapEditorToolBar->signalBoardHeightChanged.emit(3);
	qrw::g_scene.update(0);

	// Assert
	EXPECT_TRUE(zone1->containsSquare({0, 2}));
	EXPECT_FALSE(zone1->containsSquare({0, 3}));
	EXPECT_TRUE(zone2->containsSquare({2, 0}));
	EXPECT_FALSE(zone2->containsSquare({3, 0}));

	// Clean up
	qrw::g_scene.reset();
	qrw::g_scene.update(0);
}