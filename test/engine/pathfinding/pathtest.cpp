#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "engine/pathfinding/path.hpp"

#include "engine/coordinates.hpp"

class PathTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(PathTest);
	CPPUNIT_TEST(appendTest);
	CPPUNIT_TEST(forEachTest);
	CPPUNIT_TEST_SUITE_END();

	public:
		void appendTest()
		{
			qrw::Path path;

			CPPUNIT_ASSERT(path.getLength() == 0);

			qrw::Coordinates* step1 = new qrw::Coordinates(0, 0);
			path.appendStep(step1);
			CPPUNIT_ASSERT(path.getLength() == 1);
		}

		void forEachTest()
		{
			qrw::Path path;

			qrw::Coordinates* step1 = new qrw::Coordinates(0, 0);
			qrw::Coordinates* step2 = new qrw::Coordinates(1, 0);

			path.appendStep(step1);
			path.appendStep(step2);

			int counter = 0;
			for(auto step : path)
			{
				++counter;
			}

			CPPUNIT_ASSERT(counter == 2);
		}
};
CPPUNIT_TEST_SUITE_REGISTRATION(PathTest);
