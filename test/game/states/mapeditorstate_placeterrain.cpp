#include <gtest/gtest.h>

#include "game/states/mapeditorstate.hpp"

#include "engine/terrain.hpp"
#include "game/skirmish/structure.hpp"
#include "gui/scene.hpp"
#include "game/events.hpp"

#include "__mocks__/game/skirmish/gui/skirmishguifactorymock.hpp"
#include "__mocks__/game/skirmish/mapmanagermock.hpp"

using ::testing::_;
using ::testing::Return;

TEST(MapEditorState_PlaceTerrain, If_square_is_occupied_by_terrian_Then_it_is_removed)
{
	// Arrange
	SkirmishGuiFactoryMock skirmishGuiFactoryMock;
	auto mapEditorToolBar = new qrw::MapEditorToolBar(10, 10);
	EXPECT_CALL(skirmishGuiFactoryMock, createMapEditorToolBar(_, _)).WillOnce(Return(mapEditorToolBar));

	MapManagerMock mapManagerMock;
	sf::RenderWindow renderWindow;
	qrw::MapEditorState mapEditorState(&renderWindow, mapManagerMock, skirmishGuiFactoryMock);
	mapEditorState.init(nullptr);
	mapEditorToolBar->signalTerrainTypeClicked.emit(qrw::TERRAINTYPES::ET_HILL);

	auto board = qrw::g_scene.findSingleGameObject<qrw::Board>();
	auto previousTerrain = qrw::g_scene.spawn<qrw::Terrain>();
	previousTerrain->setPosition({1, 2});
	board->setTerrain({1, 2}, previousTerrain);

	// Act
	mapEditorState.handleEvent(qrw::CursorLeftClickedEvent({1, 2}));
	qrw::g_scene.update(0);

	// Assert
	auto terrains = qrw::g_scene.findGameObjects<qrw::Terrain>();
	ASSERT_EQ(terrains.size(), 1);
	EXPECT_TRUE(static_cast<qrw::Terrain*>(*terrains.begin()) != previousTerrain);

	// Cleanup
	qrw::g_scene.reset();
	qrw::g_scene.update(0);
}

TEST(MapEditorState_PlaceTerrain, If_square_is_occupied_by_structure_Then_it_is_removed)
{
	// Arrange
	SkirmishGuiFactoryMock skirmishGuiFactoryMock;
	auto mapEditorToolBar = new qrw::MapEditorToolBar(10, 10);
	EXPECT_CALL(skirmishGuiFactoryMock, createMapEditorToolBar(_, _)).WillOnce(Return(mapEditorToolBar));

	MapManagerMock mapManagerMock;
	sf::RenderWindow renderWindow;
	qrw::MapEditorState mapEditorState(&renderWindow, mapManagerMock, skirmishGuiFactoryMock);
	mapEditorState.init(nullptr);
	mapEditorToolBar->signalTerrainTypeClicked.emit(qrw::TERRAINTYPES::ET_HILL);

	auto board = qrw::g_scene.findSingleGameObject<qrw::Board>();
	auto structure = qrw::g_scene.spawn<qrw::Structure>();
	board->setStructure({1, 2}, structure);

	// Act
	mapEditorState.handleEvent(qrw::CursorLeftClickedEvent({1, 2}));
	qrw::g_scene.update(0);

	// Assert
	auto structures = qrw::g_scene.findGameObjects<qrw::Structure>();
	ASSERT_EQ(structures.size(), 0);

	// Cleanup
	qrw::g_scene.reset();
	qrw::g_scene.update(0);
}