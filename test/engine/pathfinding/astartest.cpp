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
	CPPUNIT_TEST(testGetPath);
	CPPUNIT_TEST(testGetPathNoBoard);
	CPPUNIT_TEST(testGetPathNoUnit);
	CPPUNIT_TEST(testGetPathInvalidStartOrEnd);
	CPPUNIT_TEST(testGetPathStartEqualsEnd);
	CPPUNIT_TEST(testFindLowestFCoordinates);
	CPPUNIT_TEST(testClear);
	CPPUNIT_TEST(testNodemap);
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
			qrw::Path* path = astar->getPath(*start, *end);
			CPPUNIT_ASSERT(path != 0);
			CPPUNIT_ASSERT(path->getLength() == 19);
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

		void testFindLowestFCoordinates()
		{
			// Test with an empty list
			CPPUNIT_ASSERT(astar->findLowestFCoordinates() == 0);

			// Test with only one element on openlist
			qrw::Coordinates* coords1 = new qrw::Coordinates(*start);
			astar->openlist.insert(coords1);
			CPPUNIT_ASSERT(astar->findLowestFCoordinates() == coords1);

			// Test with more than one element on openlist
			qrw::Coordinates* coords2 = new qrw::Coordinates(1, 1);
			qrw::Coordinates* coords3 = new qrw::Coordinates(2, 2);
			astar->openlist.insert(coords2);
			astar->openlist.insert(coords3);

			astar->nodemap[coords1] = new qrw::Node(*coords1);
			astar->nodemap[coords1]->setG(10);

			astar->nodemap[coords2] = new qrw::Node(*coords2);
			astar->nodemap[coords2]->setG(5);

			astar->nodemap[coords3] = new qrw::Node(*coords3);
			astar->nodemap[coords3]->setG(9);

			CPPUNIT_ASSERT(*astar->findLowestFCoordinates() == *coords2);
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

		// Just test if the node map behaves as expected.
		void testNodemap()
		{
			qrw::Coordinates* coords = new qrw::Coordinates(0, 0);
			qrw::Node* node = new qrw::Node(0, 0);

			astar->nodemap[coords] = node;

			CPPUNIT_ASSERT(astar->nodemap[coords] == node);

			qrw::Coordinates* coords2 = new qrw::Coordinates(0, 0);
			CPPUNIT_ASSERT(astar->nodemap[coords2] == node);
			CPPUNIT_ASSERT(coords != coords2);

			delete node;
			delete coords;
			delete coords2;

			astar->nodemap.clear();
		}

	private:
		qrw::AStar* astar;

		qrw::Coordinates* start;
		qrw::Coordinates* end;

		qrw::Board* board;

		qrw::Unit* walker;
};
CPPUNIT_TEST_SUITE_REGISTRATION(AStarTest);
