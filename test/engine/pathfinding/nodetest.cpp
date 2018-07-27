#include <gtest/gtest.h>

#include "engine/pathfinding/node.hpp"

TEST(Node_GetLocation, Then_correct_location_is_returned)
{
	qrw::pathfinding::Node<int> node(100);

	EXPECT_EQ(node.getLocation(), 100);
}

TEST(Node_GetF, Then_f_is_calculated_correctly)
{
	qrw::pathfinding::Node<int> node(100);
	node.setG(2);
	node.setH(10);

	EXPECT_EQ(node.getF(), 12);
};
