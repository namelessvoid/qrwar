#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock-actions.h>

#include "game/states/mapeditorstate.hpp"
#include "game/skirmish/structure.hpp"

#include "engine/board.hpp"
#include "gui/scene.hpp"

#include "game/events.hpp"

#include "__mocks__/game/skirmish/gui/skirmishguifactorymock.hpp"

using ::testing::_;
using ::testing::Return;

TEST(MapEditorState_PlaceStructure, Then_structure_is_on_scene_and_board)
{
	// Arrange
	qrw::Board* board = qrw::g_scene.spawn<qrw::Board>();
	board->setHeight(10);
	board->setWidth(10);

	SkirmishGuiFactoryMock skirmishGuiFactoryMock;
	qrw::MapEditorToolBar* mapEditorToolBar = new qrw::MapEditorToolBar(10, 10);
	EXPECT_CALL(skirmishGuiFactoryMock, createMapEditorToolBar(_, _)).WillOnce(Return(mapEditorToolBar));

	qrw::MetaManager metaManager;
	qrw::MapManager mapManager(metaManager);
	sf::RenderWindow renderWindow;
	qrw::MapEditorState mapEditorState(&renderWindow, mapManager, skirmishGuiFactoryMock);

	mapEditorState.init(nullptr);

	// Act
	mapEditorToolBar->signalStructureClicked.emit(0);
	mapEditorState.handleEvent(qrw::CursorLeftClickedEvent({1, 2}));

	// Assert
	auto structures = qrw::g_scene.findGameObjects<qrw::Structure>();
	ASSERT_EQ(structures.size(), 1);

	// Clean up
	qrw::g_scene.reset();
	qrw::g_scene.update(0);
}
