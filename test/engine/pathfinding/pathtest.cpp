#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "engine/pathfinding/path.hpp"

class PathTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(PathTest);
	CPPUNIT_TEST(testPrependStep);
	CPPUNIT_TEST(testAppendStep);
	CPPUNIT_TEST(testGetStep);
	CPPUNIT_TEST(testForEach);
	CPPUNIT_TEST_SUITE_END();

	public:
		void testAppendStep()
		{
			qrw::pathfinding::Path path;

			CPPUNIT_ASSERT(path.getLength() == 0);

			qrw::Coordinates step1(12, 13);
			path.appendStep(step1);
			CPPUNIT_ASSERT(path.getLength() == 1);
			CPPUNIT_ASSERT(path.getMovementCosts() == 0);
		}

		void testPrependStep()
		{
			qrw::pathfinding::Path path;

			qrw::Coordinates step1(0, 0);
			qrw::Coordinates step2(1, 0);

			path.prependStep(step2);
			path.prependStep(step1);

			int counter = 0;
			for(auto step : path)
			{
				CPPUNIT_ASSERT(step.getX() == counter);
				++counter;
			}
		}

		void testGetStep()
		{
			qrw::pathfinding::Path path;

			qrw::Coordinates step1(0, 0);
			qrw::Coordinates step2(1, 0);

			path.appendStep(step1);
			path.appendStep(step2);

			CPPUNIT_ASSERT(path.getStep(0) == step1);
			CPPUNIT_ASSERT(path.getStep(1) == step2);
		}

		void testForEach()
		{
			qrw::pathfinding::Path path;

			qrw::Coordinates step1(0, 10);
			qrw::Coordinates step2(1, 11);

			path.appendStep(step1);
			path.appendStep(step2);

			int counter = 0;
			for(auto step : path)
			{
				CPPUNIT_ASSERT(step.getX() == counter);
				CPPUNIT_ASSERT(step.getY() == (counter + 10));
				++counter;
			}

			CPPUNIT_ASSERT(counter == 2);
		}
};
CPPUNIT_TEST_SUITE_REGISTRATION(PathTest);
