#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock-actions.h>

#include "game/states/mapeditorstate.hpp"
#include "game/skirmish/structure.hpp"

#include "engine/board.hpp"
#include "engine/terrain.hpp"
#include "gui/scene.hpp"

#include "game/events.hpp"

#include "__mocks__/game/skirmish/gui/skirmishguifactorymock.hpp"
#include "__mocks__/game/skirmish/mapmanagermock.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::NotNull;

TEST(MapEditorState_PlaceStructure, Then_structure_is_on_scene_and_board)
{
	// Arrange
	SkirmishGuiFactoryMock skirmishGuiFactoryMock;
	auto mapEditorToolBar = new qrw::MapEditorToolBar(10, 10);
	EXPECT_CALL(skirmishGuiFactoryMock, createMapEditorToolBar(_, _)).WillOnce(Return(mapEditorToolBar));

	MapManagerMock mapManagerMock;
	sf::RenderWindow renderWindow;
	qrw::MapEditorState mapEditorState(&renderWindow, mapManagerMock, skirmishGuiFactoryMock);
	mapEditorState.init(nullptr);

	// Act
	mapEditorToolBar->signalStructureClicked.emit(0);
	mapEditorState.handleEvent(qrw::CursorLeftClickedEvent({1, 2}));

	// Assert
	auto structures = qrw::g_scene.findGameObjects<qrw::Structure>();
	ASSERT_EQ(structures.size(), 1);

	auto board = qrw::g_scene.findSingleGameObject<qrw::Board>();
	EXPECT_THAT(board->getStructure({1, 2}), NotNull());

	// Clean up
	qrw::g_scene.reset();
	qrw::g_scene.update(0);
}

TEST(MapEditorState_PlaceStructure, If_square_is_occupied_by_structure_Then_it_is_removed_first)
{
	// Arrange
	SkirmishGuiFactoryMock skirmishGuiFactoryMock;
	auto mapEditorToolBar = new qrw::MapEditorToolBar(10, 10);
	EXPECT_CALL(skirmishGuiFactoryMock, createMapEditorToolBar(_, _)).WillOnce(Return(mapEditorToolBar));

	MapManagerMock mapManagerMock;
	sf::RenderWindow renderWindow;
	qrw::MapEditorState mapEditorState(&renderWindow, mapManagerMock, skirmishGuiFactoryMock);
	mapEditorState.init(nullptr);

	mapEditorToolBar->signalStructureClicked.emit(0);

	auto board = qrw::g_scene.findSingleGameObject<qrw::Board>();
	auto previousStructure = qrw::g_scene.spawn<qrw::Structure>();
	board->setStructure({1, 2}, previousStructure);

	// Act
	mapEditorState.handleEvent(qrw::CursorLeftClickedEvent({1, 2}));

	qrw::g_scene.update(0);

	// Assert
	auto structures = qrw::g_scene.findGameObjects<qrw::Structure>();
	ASSERT_EQ(structures.size(), 1);
	EXPECT_TRUE(static_cast<qrw::Structure*>(*structures.begin()) != previousStructure);

	// Cleanup
	qrw::g_scene.reset();
	qrw::g_scene.update(0);
}

TEST(MapEditorState_PlaceStructure, If_square_is_occupied_by_terrian_Then_it_is_removed_first)
{
	// Arrange
	SkirmishGuiFactoryMock skirmishGuiFactoryMock;
	auto mapEditorToolBar = new qrw::MapEditorToolBar(10, 10);
	EXPECT_CALL(skirmishGuiFactoryMock, createMapEditorToolBar(_, _)).WillOnce(Return(mapEditorToolBar));

	MapManagerMock mapManagerMock;
	sf::RenderWindow renderWindow;
	qrw::MapEditorState mapEditorState(&renderWindow, mapManagerMock, skirmishGuiFactoryMock);
	mapEditorState.init(nullptr);
	mapEditorToolBar->signalStructureClicked.emit(0);

	auto board = qrw::g_scene.findSingleGameObject<qrw::Board>();
	auto previousTerrain = qrw::g_scene.spawn<qrw::Terrain>();
	board->setTerrain({1, 2}, previousTerrain);

	// Act
	mapEditorState.handleEvent(qrw::CursorLeftClickedEvent({1, 2}));

	qrw::g_scene.update(0);

	// Assert
	auto terrains = qrw::g_scene.findGameObjects<qrw::Terrain>();
	EXPECT_EQ(terrains.size(), 0);

	// Cleanup
	qrw::g_scene.reset();
	qrw::g_scene.update(0);
}