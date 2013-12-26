#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "engine/coordinates.hpp"

class CoordinatesTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(CoordinatesTest);
	CPPUNIT_TEST(test);
	CPPUNIT_TEST_SUITE_END();

	public:
		void test()
		{
			qrw::Coordinates coords(3);

			CPPUNIT_ASSERT(coords.getX() == 3);
			CPPUNIT_ASSERT(coords.getY() == 0);

			coords.setY(12);
			CPPUNIT_ASSERT(coords.getY() == 12);

			coords.setX(4);
			CPPUNIT_ASSERT(coords.getX() == 4);
		}
};

CPPUNIT_TEST_SUITE_REGISTRATION(CoordinatesTest);
