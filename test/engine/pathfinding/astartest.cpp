#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "engine/board.hpp"
#include "engine/unit.hpp"
#include "engine/pathfinding/node.hpp"

#define private public
#include "engine/pathfinding/astar.hpp"
#undef private

class AStarTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(AStarTest);
	CPPUNIT_TEST(testGetPath);
	CPPUNIT_TEST(testGetPathNoBoard);
	CPPUNIT_TEST(testGetPathNoUnit);
	CPPUNIT_TEST(testGetPathInvalidStartOrEnd);
	CPPUNIT_TEST(testGetPathStartEqualsEnd);
	CPPUNIT_TEST(testClear);
	CPPUNIT_TEST_SUITE_END();

	public:
		void setUp()
		{
			astar = new qrw::AStar();

			start = new qrw::Coordinates(0, 0);
			end   = new qrw::Coordinates(9, 9);

			board = new qrw::Board(10, 10);

			walker = new qrw::Unit(qrw::EUT_SWORDMAN, 100, 2, 2, 2, 10, 0);
			board->getSquare(0, 0)->setUnit(walker);

			astar->setBoard(board);
		}

		void tearDown()
		{
			delete astar;
			delete start;
			delete end;
			delete walker;
		}

		void testGetPath()
		{
			CPPUNIT_ASSERT(astar->getPath(*start, *end) != 0);
		}

		void testGetPathNoBoard()
		{
			astar->setBoard(0);
			CPPUNIT_ASSERT(astar->getPath(*start, *end) == 0);
		}

		void testGetPathInvalidStartOrEnd()
		{
			qrw::Coordinates invalid(-1, 0);

			CPPUNIT_ASSERT(astar->getPath(invalid, *end) == 0);
			CPPUNIT_ASSERT(astar->getPath(*start, invalid) == 0);
		}

		void testGetPathNoUnit()
		{
			board->getSquare(*start)->setUnit(0);

			CPPUNIT_ASSERT(astar->getPath(*start, *end) == 0);
		}

		void testGetPathStartEqualsEnd()
		{
			qrw::Coordinates equalend(*start);
			CPPUNIT_ASSERT(astar->getPath(*start, equalend) == 0);
		}

		void testClear()
		{
			qrw::Coordinates* startcopy = new qrw::Coordinates(*start);
			qrw::Coordinates* endcopy = new qrw::Coordinates(*end);

			qrw::Node* node = new qrw::Node(*start);

			astar->openlist.insert(startcopy);
			astar->closedlist.insert(endcopy);
			astar->closedlist.insert(startcopy);
			astar->nodemap[startcopy] = node;
			astar->clear();

			CPPUNIT_ASSERT(astar->openlist.size() == 0);
			CPPUNIT_ASSERT(astar->closedlist.size() == 0);
			CPPUNIT_ASSERT(astar->nodemap.size() == 0);
		}

	private:
		qrw::AStar* astar;

		qrw::Coordinates* start;
		qrw::Coordinates* end;

		qrw::Board* board;

		qrw::Unit* walker;
};
CPPUNIT_TEST_SUITE_REGISTRATION(AStarTest);
