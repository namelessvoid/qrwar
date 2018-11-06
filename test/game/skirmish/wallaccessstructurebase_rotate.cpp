#include <gtest/gtest.h>

#include "__mocks__/game/skirmish/wallaccessstructuremock.hpp"

TEST(WallAccessStructureBase_Rotate, Then_directions_cycle_clockwise)
{
	// Arrange
	WallAccessStructureMock wallAccess;

	// Act
	ASSERT_EQ(wallAccess.getFace(), qrw::Directions::NORTH);
	wallAccess.rotate();
	ASSERT_EQ(wallAccess.getFace(), qrw::Directions::EAST);
	wallAccess.rotate();
	ASSERT_EQ(wallAccess.getFace(), qrw::Directions::SOUTH);
	wallAccess.rotate();
	ASSERT_EQ(wallAccess.getFace(), qrw::Directions::WEST);
	wallAccess.rotate();
	ASSERT_EQ(wallAccess.getFace(), qrw::Directions::NORTH);
}