#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "engine/pathfinding/node.hpp"
#include "engine/coordinates.hpp"

class NodeTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(NodeTest);
	CPPUNIT_TEST(testCtorCoordinate);
	CPPUNIT_TEST(testGetF);
	CPPUNIT_TEST_SUITE_END();

	public:
		void testCtorCoordinate()
		{
			qrw::Coordinates coord(2, 3);
			qrw::Node node(coord);

			CPPUNIT_ASSERT(node == coord);
		}

		void testGetF()
		{
			qrw::Node node(0, 0);
			node.setG(2);
			node.setH(10);

			CPPUNIT_ASSERT(node.getF() == 12);
		}
};

CPPUNIT_TEST_SUITE_REGISTRATION(NodeTest);
