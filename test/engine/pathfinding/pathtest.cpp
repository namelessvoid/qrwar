#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "engine/pathfinding/path.hpp"

#include "engine/square.hpp"

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

			qrw::Square* step1 = new qrw::Square(0, 0);
			path.appendStep(step1);
			CPPUNIT_ASSERT(path.getLength() == 1);
		}

		void forEachTest()
		{
			qrw::Path path;

			qrw::Square* step1 = new qrw::Square(0, 10);
			qrw::Square* step2 = new qrw::Square(1, 11);

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
