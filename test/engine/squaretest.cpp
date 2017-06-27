#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "engine/square.hpp"
#include "engine/unit.hpp"

class SquareTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(SquareTest);
	CPPUNIT_TEST(getDistanceTest);
	CPPUNIT_TEST(testIsAccessible);
	CPPUNIT_TEST_SUITE_END();

	public:
		void getDistanceTest()
		{
			qrw::Square square0_0(0, 0);
			qrw::Square square0_0_1(0, 0);
			qrw::Square square1_0(1, 0);
			qrw::Square square1_1(1, 1);
			qrw::Square square2_1(2, 1);
			qrw::Square square2_0(2, 0);
			qrw::Square square_2_1(-2, 1);

			CPPUNIT_ASSERT(square0_0.getDistance(&square0_0_1) == 0);
			CPPUNIT_ASSERT(square0_0.getDistance(&square1_0) == 1);
			CPPUNIT_ASSERT(square0_0.getDistance(&square1_0) == 1);
			CPPUNIT_ASSERT(square0_0.getDistance(&square1_1) == 2);
			CPPUNIT_ASSERT(square0_0.getDistance(&square2_1) == 3);
			CPPUNIT_ASSERT(square0_0.getDistance(&square2_0) == 2);
			CPPUNIT_ASSERT(square0_0.getDistance(&square_2_1) == 3);
		}

		void testIsAccessible()
		{
			qrw::Square square(0, 0);
			qrw::Unit::Ptr unit = qrw::Unit::createUnit(qrw::EUT_SWORDMAN, nullptr, nullptr);

			CPPUNIT_ASSERT(square.isAccessible() == true);

			square.setUnit(unit);
			CPPUNIT_ASSERT(square.isAccessible() == false);
		}
};

CPPUNIT_TEST_SUITE_REGISTRATION(SquareTest);
