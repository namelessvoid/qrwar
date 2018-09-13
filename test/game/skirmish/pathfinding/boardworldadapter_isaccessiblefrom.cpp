#include <gtest/gtest.h>
#include <game/skirmish/stairs.hpp>
#include <game/skirmish/wall.hpp>

#include "engine/board.hpp"

TEST(BoardWorldAdapter_IsAccessibleFrom, PlainToPlain)
{
	// Arrange
	qrw::Board board;
	board.setHeight(5);
	board.setWidth(5);

	qrw::BoardWorldAdapter adapter(board);

	// Act
	bool isAccessible = adapter.isAccessibleFrom({0, 0}, {0, 1});

	// Assert
	EXPECT_TRUE(isAccessible);
}

TEST(BoardWorldAdapter_IsAccessibleFrom, PlainToStairs)
{
	// Arrange
	qrw::Board board;
	board.setHeight(5);
	board.setWidth(5);

	qrw::BoardWorldAdapter adapter(board);

	qrw::Stairs stairs;
	stairs.setPosition({1, 1});
	board.setStructure(stairs.getPosition(), &stairs);

	ASSERT_EQ(stairs.getFace(), qrw::Directions::NORTH) << "Precondition failed: Stairs not facing NORTH";

	// Act & Assert Plain->Stairs
	EXPECT_FALSE(adapter.isAccessibleFrom(stairs.getPosition() + qrw::Directions::NORTH, stairs.getPosition()));
	EXPECT_TRUE(adapter.isAccessibleFrom(stairs.getPosition() + qrw::Directions::EAST, stairs.getPosition()));
	EXPECT_TRUE(adapter.isAccessibleFrom(stairs.getPosition() + qrw::Directions::SOUTH, stairs.getPosition()));
	EXPECT_TRUE(adapter.isAccessibleFrom(stairs.getPosition() + qrw::Directions::WEST, stairs.getPosition()));

	// Act & Assert Stairs->Plain
	EXPECT_FALSE(adapter.isAccessibleFrom(stairs.getPosition(), stairs.getPosition() + qrw::Directions::NORTH));
	EXPECT_TRUE(adapter.isAccessibleFrom(stairs.getPosition(), stairs.getPosition() + qrw::Directions::EAST));
	EXPECT_TRUE(adapter.isAccessibleFrom(stairs.getPosition(), stairs.getPosition() + qrw::Directions::SOUTH));
	EXPECT_TRUE(adapter.isAccessibleFrom(stairs.getPosition(), stairs.getPosition() + qrw::Directions::WEST));
}

TEST(BoardWorldAdapter_IsAccessibleFrom, PlainToWall)
{
	// Arrange
	qrw::Board board;
	board.setHeight(5);
	board.setWidth(5);

	qrw::BoardWorldAdapter adapter(board);

	qrw::Wall wall;
	wall.setPosition({1, 1});
	board.setStructure(wall.getPosition(), &wall);

	// Act & Assert Plain->Wall
	EXPECT_FALSE(adapter.isAccessibleFrom(wall.getPosition() + qrw::Directions::NORTH, wall.getPosition()));
	EXPECT_FALSE(adapter.isAccessibleFrom(wall.getPosition() + qrw::Directions::EAST, wall.getPosition()));
	EXPECT_FALSE(adapter.isAccessibleFrom(wall.getPosition() + qrw::Directions::SOUTH, wall.getPosition()));
	EXPECT_FALSE(adapter.isAccessibleFrom(wall.getPosition() + qrw::Directions::WEST, wall.getPosition()));

	// Act & Assert Wall->Plain
	EXPECT_FALSE(adapter.isAccessibleFrom(wall.getPosition(), wall.getPosition() + qrw::Directions::NORTH));
	EXPECT_FALSE(adapter.isAccessibleFrom(wall.getPosition(), wall.getPosition() + qrw::Directions::EAST));
	EXPECT_FALSE(adapter.isAccessibleFrom(wall.getPosition(), wall.getPosition() + qrw::Directions::SOUTH));
	EXPECT_FALSE(adapter.isAccessibleFrom(wall.getPosition(), wall.getPosition() + qrw::Directions::WEST));
}

TEST(BoardWorldAdapter_IsAccessibleFrom, StairsToStairs)
{
	// Arrange
	qrw::Board board;
	board.setHeight(5);
	board.setWidth(5);

	qrw::BoardWorldAdapter adapter(board);

	qrw::Stairs stairs1;
	stairs1.setPosition({0, 0});
	board.setStructure(stairs1.getPosition(), &stairs1);

	qrw::Stairs stairs2;
	stairs2.setPosition({0, 1});
	board.setStructure(stairs2.getPosition(), &stairs2);

	// Act & Assert
	EXPECT_TRUE(adapter.isAccessibleFrom(stairs1.getPosition(), stairs2.getPosition()));
}

TEST(BoardWorldAdapter_IsAccessibleFrom, StairsToWall)
{
	// Arrange
	qrw::Board board;
	board.setHeight(5);
	board.setWidth(5);

	qrw::BoardWorldAdapter adapter(board);

	qrw::Stairs stairs;
	stairs.setPosition({1, 1});
	board.setStructure(stairs.getPosition(), &stairs);

	qrw::Wall wall;

	ASSERT_EQ(stairs.getFace(), qrw::Directions::NORTH) << "Precondition failed: Stairs not facing NORTH";

	// Assert NORTH
	wall.setPosition(stairs.getPosition() + qrw::Directions::NORTH);
	board.setStructure(wall.getPosition(), &wall);
	EXPECT_TRUE(adapter.isAccessibleFrom(stairs.getPosition() + qrw::Directions::NORTH, stairs.getPosition()));
	EXPECT_TRUE(adapter.isAccessibleFrom(stairs.getPosition(), stairs.getPosition() + qrw::Directions::NORTH));

	// Assert EAST
	board.removeStructureAt(wall.getPosition());
	wall.setPosition(stairs.getPosition() + qrw::Directions::EAST);
	board.setStructure(wall.getPosition(), &wall);
	EXPECT_FALSE(adapter.isAccessibleFrom(stairs.getPosition() + qrw::Directions::EAST, stairs.getPosition()));
	EXPECT_FALSE(adapter.isAccessibleFrom(stairs.getPosition(), stairs.getPosition() + qrw::Directions::EAST));

	// Assert SOUTH
	board.removeStructureAt(wall.getPosition());
	wall.setPosition(stairs.getPosition() + qrw::Directions::SOUTH);
	board.setStructure(wall.getPosition(), &wall);
	EXPECT_FALSE(adapter.isAccessibleFrom(stairs.getPosition() + qrw::Directions::SOUTH, stairs.getPosition()));
	EXPECT_FALSE(adapter.isAccessibleFrom(stairs.getPosition(), stairs.getPosition() + qrw::Directions::SOUTH));

	// Assert WEST
	board.removeStructureAt(wall.getPosition());
	wall.setPosition(stairs.getPosition() + qrw::Directions::WEST);
	board.setStructure(wall.getPosition(), &wall);
	EXPECT_FALSE(adapter.isAccessibleFrom(stairs.getPosition() + qrw::Directions::WEST, stairs.getPosition()));
	EXPECT_FALSE(adapter.isAccessibleFrom(stairs.getPosition(), stairs.getPosition() + qrw::Directions::WEST));
}

TEST(BoardWorldAdapter_IsAccessibleFrom, WallToWall)
{
	// Arrange
	qrw::Board board;
	board.setHeight(5);
	board.setWidth(5);

	qrw::BoardWorldAdapter adapter(board);

	qrw::Wall wall1;
	wall1.setPosition({0, 0});
	board.setStructure(wall1.getPosition(), &wall1);

	qrw::Wall wall2;
	wall2.setPosition({0, 1});
	board.setStructure(wall2.getPosition(), &wall2);

	// Act & Assert
	EXPECT_TRUE(adapter.isAccessibleFrom(wall1.getPosition(), wall2.getPosition()));
}