#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#define private public
#include "engine/pathfinding/astar.hpp"
#undef private

class AStarTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(AStarTest);
	CPPUNIT_TEST(testGetPath);
	CPPUNIT_TEST(testClear);
	CPPUNIT_TEST_SUITE_END();

	public:
		void setUp()
		{
			astar = new qrw::AStar();

			start = new qrw::Coordinates(0, 0);
			end   = new qrw::Coordinates(0, 0);
		}

		void tearDown()
		{
			delete astar;
			delete start;
			delete end;
		}

		void testGetPath()
		{
			CPPUNIT_ASSERT(astar->getPath(*start, *end) == 0);
		}

		void testClear()
		{
			qrw::Coordinates* startcopy = new qrw::Coordinates(*start);
			qrw::Coordinates* endcopy = new qrw::Coordinates(*end);

			astar->openlist.insert(startcopy);
			astar->closedlist.insert(endcopy);
			astar->clear();

			CPPUNIT_ASSERT(astar->openlist.size() == 0);
			CPPUNIT_ASSERT(astar->closedlist.size() == 0);
		}

	private:
		qrw::AStar* astar;

		qrw::Coordinates* start;
		qrw::Coordinates* end;
};
CPPUNIT_TEST_SUITE_REGISTRATION(AStarTest);
