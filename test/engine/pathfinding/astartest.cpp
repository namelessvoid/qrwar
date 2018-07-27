#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "engine/board.hpp"
#include "engine/unit.hpp"
#include "engine/pathfinding/node.hpp"
#include "engine/pathfinding/path.hpp"

#define private public
#include "engine/pathfinding/astar.hpp"
#undef private

using ::testing::NotNull;
using ::testing::IsNull;
//
//void setUp()
//{
//	astar = new qrw::pathfinding::AStar();
//
//	start = qrw::Coordinates(0, 0);
//	end   = qrw::Coordinates(9, 9);
//
//	board = new qrw::Board(10, 10);
//	boardWorldAdapter = new qrw::BoardWorldAdapter(*board);
//
//	walker  = qrw::Unit::createUnit(qrw::EUT_SWORDMAN, nullptr);
//	blocker = qrw::Unit::createUnit(qrw::EUT_SWORDMAN, nullptr);
//	board->setUnit({0, 0}, walker);
//
//	astar->setWorldAdapter(*boardWorldAdapter);
//}
//
//void tearDown()
//{
//	delete board;
//	delete boardWorldAdapter;
//	delete astar;
//}

TEST(AStar_FindPath, If_no_obstacles_block_the_way_Then_straight_path_is_found)
{
	qrw::Board board(10, 10);

	qrw::Unit unit;
	board.setUnit({0, 0}, &unit);

	qrw::BoardWorldAdapter boardWorldAdapter(board);
	qrw::pathfinding::AStar astar;
	astar.setWorldAdapter(boardWorldAdapter);

	qrw::pathfinding::Path* path = astar.findPath(qrw::Coordinates(0, 0), qrw::Coordinates(9, 9));
	ASSERT_TRUE(path != nullptr);
	EXPECT_EQ(path->getLength(), 19);

	int counterx = 0;
	int countery = 0;
	auto stepiter =  path->begin();

	while(countery < 9)
	{
		EXPECT_EQ((*stepiter), qrw::Coordinates(counterx, countery));
		++stepiter;
		++countery;
	}

	while(counterx <= 9)
	{
		EXPECT_EQ((*stepiter), qrw::Coordinates(counterx, countery));
		++stepiter;
		++counterx;
	}

	delete path;
}

TEST(AStar_FindPath, If_obastacles_block_the_way_Then_path_is_found)
{
	qrw::Board board(10, 10);

	qrw::Unit unit;
	board.setUnit({0, 0}, &unit);

	qrw::Unit blocker;

	qrw::BoardWorldAdapter boardWorldAdapter(board);
	qrw::pathfinding::AStar astar;
	astar.setWorldAdapter(boardWorldAdapter);

	// Prepare board
	for(int i = 2; i <= 5; ++i)
		board.setUnit({2, i}, &blocker);
	for(int i = 0; i <= 1; ++i)
		board.setUnit({i, 5}, &blocker);
	for(int i = 0; i <= 4; ++i)
		board.setUnit({4, i}, &blocker);
	for(int i = 3; i <= 7; ++i)
		board.setUnit({6, i}, &blocker);
	for(int i = 6; i <= 9; ++i)
		board.setUnit({8, i}, &blocker);
	board.setUnit({4, 6}, &blocker);
	board.setUnit({3, 7}, &blocker);

	qrw::pathfinding::Path* path = astar.findPath({0, 0}, {9, 9});
	ASSERT_THAT(path, NotNull());
	EXPECT_EQ(path->getLength(), 25);
	EXPECT_EQ((*(path->begin() + 14)), qrw::Coordinates(6, 8));

	delete path;
}

TEST(AStar_FindPath, If_end_is_not_accessible_Then_null_is_returned)
{
	class BoardWorldAdapterMock : public qrw::BoardWorldAdapter
	{
	public:
		explicit BoardWorldAdapterMock(const qrw::Board& board) : BoardWorldAdapter(board)
		{}

		bool isAccessible(const qrw::Coordinates& location) const override
		{ return false; }
	};

	qrw::Board board(10, 10);

	qrw::Unit unit;
	board.setUnit({0, 0}, &unit);

	BoardWorldAdapterMock boardWorldAdapter(board);
	qrw::pathfinding::AStar astar;
	astar.setWorldAdapter(boardWorldAdapter);

	qrw::Coordinates invalid(0, 0);

	ASSERT_THAT(astar.findPath({0, 0}, {0, 1}), IsNull());
}

TEST(AStar_FindPath, If_start_equals_end_Then_null_is_returned)
{
	qrw::Board board(10, 10);

	qrw::Unit unit;
	board.setUnit({0, 0}, &unit);

	qrw::BoardWorldAdapter boardWorldAdapter(board);
	qrw::pathfinding::AStar astar;
	astar.setWorldAdapter(boardWorldAdapter);

	ASSERT_THAT(astar.findPath({1, 1}, {1, 1}), IsNull());
}

/**
 * @see https://github.com/namelessvoid/qrwar/issues/67
 */
TEST(AStar_FindPath, If_subsequent_calls_cannot_find_valid_paths_Then_all_returned_paths_are_null)
{
	qrw::Board board(10, 10);

	qrw::Unit unit;
	board.setUnit({0, 0}, &unit);
	board.setUnit({0, 1}, &unit);

	qrw::BoardWorldAdapter boardWorldAdapter(board);
	qrw::pathfinding::AStar astar;
	astar.setWorldAdapter(boardWorldAdapter);

	EXPECT_THAT(astar.findPath({0, 0}, {0, 1}), IsNull());
	EXPECT_THAT(astar.findPath({0, 1}, {0, 0}), IsNull());
}

//
//void testFindLowestFCoordinates()
//{
//	// Test with an empty list
//	CPPUNIT_ASSERT(astar->findLowestFCoordinates() == qrw::Coordinates(0, 0));
//
//	// Test with only one element on openlist
//	astar->_openlist.insert(start);
//	CPPUNIT_ASSERT(astar->findLowestFCoordinates() == start);
//
//	// Test with more than one element on openlist
//	qrw::Coordinates coords2(1, 1);
//	qrw::Coordinates coords3(2, 2);
//	astar->_openlist.insert(coords2);
//	astar->_openlist.insert(coords3);
//
//	astar->_nodemap[start] = new qrw::pathfinding::Node(start);
//	astar->_nodemap[start]->setG(10);
//
//	astar->_nodemap[coords2] = new qrw::pathfinding::Node(coords2);
//	astar->_nodemap[coords2]->setG(5);
//
//	astar->_nodemap[coords3] = new qrw::pathfinding::Node(coords3);
//	astar->_nodemap[coords3]->setG(9);
//
//	CPPUNIT_ASSERT(astar->findLowestFCoordinates() == coords2);
//}
//
//void testClear()
//{
//	qrw::pathfinding::Node* node = new qrw::pathfinding::Node(start);
//
//	astar->_openlist.insert(start);
//	astar->_closedlist.insert(end);
//	astar->_closedlist.insert(start);
//	astar->_nodemap[start] = node;
//	astar->clear();
//
//	CPPUNIT_ASSERT(astar->_openlist.size() == 0);
//	CPPUNIT_ASSERT(astar->_closedlist.size() == 0);
//	CPPUNIT_ASSERT(astar->_nodemap.size() == 0);
//}
//
//// Just test if the node map behaves as expected.
//void testNodemap()
//{
//	qrw::Coordinates coords(0, 0);
//	qrw::pathfinding::Node* node = new qrw::pathfinding::Node(0, 0);
//
//	astar->_nodemap[coords] = node;
//
//	CPPUNIT_ASSERT(astar->_nodemap[coords] == node);
//
//	qrw::Coordinates coords2(0, 0);
//	CPPUNIT_ASSERT(astar->_nodemap[coords2] == node);
//	CPPUNIT_ASSERT(coords != coords2);
//
//	delete node;
//
//	astar->_nodemap.clear();
//}
//

