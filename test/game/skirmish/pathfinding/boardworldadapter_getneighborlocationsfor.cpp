#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "engine/board.hpp"
#include "game/skirmish/pathfinding/boardworldadapter.hpp"

using ::testing::Contains;

TEST(BoardWorldAdapter_GetNeighborLocationsFor, Then_list_contains_all_neighbors)
{
	// Arrange
	qrw::Board board(10, 10);
	qrw::BoardWorldAdapter boardWorldAdapter(board);

	// Act
	std::vector<qrw::Coordinates> neighbors = boardWorldAdapter.getNeighborLocationsFor({5, 5});

	// Assert
	EXPECT_EQ(neighbors.size(), 4);
	EXPECT_THAT(neighbors, Contains(qrw::Coordinates(4, 5)));
	EXPECT_THAT(neighbors, Contains(qrw::Coordinates(5, 4)));
	EXPECT_THAT(neighbors, Contains(qrw::Coordinates(6, 5)));
	EXPECT_THAT(neighbors, Contains(qrw::Coordinates(5, 6)));
}