#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "engine/board.hpp"
#include "engine/unit.hpp"
#include "engine/pathfinding/node.hpp"
#include "engine/pathfinding/path.hpp"

#define private public
#include "engine/pathfinding/astar.hpp"
#undef private

class AStarTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(AStarTest);
	CPPUNIT_TEST(testFindPath);
	CPPUNIT_TEST(testFindPath2);
	CPPUNIT_TEST(testFindPathNoBoard);
	CPPUNIT_TEST(testFindPathInvalidStartOrEnd);
	CPPUNIT_TEST(testFindPathStartEqualsEnd);
	CPPUNIT_TEST(testFindLowestFCoordinates);
	CPPUNIT_TEST(testClear);
	CPPUNIT_TEST(testNodemap);
	CPPUNIT_TEST(testBug_67);
	CPPUNIT_TEST_SUITE_END();

	public:
		void setUp()
		{
			astar = new qrw::pathfinding::AStar();

			start = qrw::Coordinates(0, 0);
			end   = qrw::Coordinates(9, 9);

			board = new qrw::Board(10, 10);

			walker  = qrw::Unit::createUnit(qrw::EUT_SWORDMAN, nullptr);
			blocker = qrw::Unit::createUnit(qrw::EUT_SWORDMAN, nullptr);
			board->setUnit({0, 0}, walker);

			astar->setBoard(board);
		}

		void tearDown()
		{
			delete board;
			delete astar;
		}

		void testFindPath()
		{
			qrw::pathfinding::Path* path = astar->findPath(start, end);
			CPPUNIT_ASSERT(path != 0);
			CPPUNIT_ASSERT(path->getLength() == 19);

			int counterx = 0;
			int countery = 0;
			auto stepiter =  path->begin();

			while(countery < 9)
			{
				CPPUNIT_ASSERT((*stepiter) == qrw::Coordinates(counterx, countery));
				++stepiter;
				++countery;
			}

			while(counterx <= 9)
			{
				CPPUNIT_ASSERT((*stepiter) == qrw::Coordinates(counterx, countery));
				++stepiter;
				++counterx;
			}
			delete path;
		}

		void testFindPath2()
		{
			// Prepare board
			for(int i = 2; i <= 5; ++i)
				board->setUnit({2, i}, blocker);
			for(int i = 0; i <= 1; ++i)
				board->setUnit({i, 5}, blocker);
			for(int i = 0; i <= 4; ++i)
				board->setUnit({4, i}, blocker);
			for(int i = 3; i <= 7; ++i)
				board->setUnit({6, i}, blocker);
			for(int i = 6; i <= 9; ++i)
				board->setUnit({8, i}, blocker);
			board->setUnit({4, 6}, blocker);
			board->setUnit({3, 7}, blocker);

			qrw::pathfinding::Path* path = astar->findPath(start, end);
			CPPUNIT_ASSERT(path != 0);
			CPPUNIT_ASSERT(path->getLength() == 25);
			CPPUNIT_ASSERT((*(path->begin() + 14)) == qrw::Coordinates(6, 8));
			delete path;
		}

		void testFindPathNoBoard()
		{
			astar->setBoard(0);
			CPPUNIT_ASSERT(astar->findPath(start, end) == 0);
		}

		void testFindPathInvalidStartOrEnd()
		{
			qrw::Coordinates invalid(-1, 0);

			CPPUNIT_ASSERT(astar->findPath(invalid, end) == 0);
			CPPUNIT_ASSERT(astar->findPath(start, invalid) == 0);
		}

		void testFindPathStartEqualsEnd()
		{
			qrw::Coordinates equalend(start);
			CPPUNIT_ASSERT(astar->findPath(start, equalend) == 0);
		}

		void testFindLowestFCoordinates()
		{
			// Test with an empty list
			CPPUNIT_ASSERT(astar->findLowestFCoordinates() == qrw::Coordinates(0, 0));

			// Test with only one element on openlist
			astar->_openlist.insert(start);
			CPPUNIT_ASSERT(astar->findLowestFCoordinates() == start);

			// Test with more than one element on openlist
			qrw::Coordinates coords2(1, 1);
			qrw::Coordinates coords3(2, 2);
			astar->_openlist.insert(coords2);
			astar->_openlist.insert(coords3);

			astar->_nodemap[start] = new qrw::pathfinding::Node(start);
			astar->_nodemap[start]->setG(10);

			astar->_nodemap[coords2] = new qrw::pathfinding::Node(coords2);
			astar->_nodemap[coords2]->setG(5);

			astar->_nodemap[coords3] = new qrw::pathfinding::Node(coords3);
			astar->_nodemap[coords3]->setG(9);

			CPPUNIT_ASSERT(astar->findLowestFCoordinates() == coords2);
		}

		void testClear()
		{
			qrw::pathfinding::Node* node = new qrw::pathfinding::Node(start);

			astar->_openlist.insert(start);
			astar->_closedlist.insert(end);
			astar->_closedlist.insert(start);
			astar->_nodemap[start] = node;
			astar->clear();

			CPPUNIT_ASSERT(astar->_openlist.size() == 0);
			CPPUNIT_ASSERT(astar->_closedlist.size() == 0);
			CPPUNIT_ASSERT(astar->_nodemap.size() == 0);
		}

		// Just test if the node map behaves as expected.
		void testNodemap()
		{
			qrw::Coordinates coords(0, 0);
			qrw::pathfinding::Node* node = new qrw::pathfinding::Node(0, 0);

			astar->_nodemap[coords] = node;

			CPPUNIT_ASSERT(astar->_nodemap[coords] == node);

			qrw::Coordinates coords2(0, 0);
			CPPUNIT_ASSERT(astar->_nodemap[coords2] == node);
			CPPUNIT_ASSERT(coords != coords2);

			delete node;

			astar->_nodemap.clear();
		}

		/**
		 * @see https://github.com/namelessvoid/qrwar/issues/67
		 */
		void testBug_67()
		{
			board->setUnit({1, 0}, blocker);
			CPPUNIT_ASSERT(0 == astar->findPath(start, qrw::Coordinates(1, 0)));
			qrw::pathfinding::Path* path = astar->findPath(qrw::Coordinates(1, 0), start);
			CPPUNIT_ASSERT(0 == path);
		}

	private:
		qrw::pathfinding::AStar* astar;

		qrw::Coordinates start;
		qrw::Coordinates end;

		qrw::Board* board;

		qrw::Unit* walker;
		qrw::Unit* blocker;
};
//CPPUNIT_TEST_SUITE_REGISTRATION(AStarTest);
