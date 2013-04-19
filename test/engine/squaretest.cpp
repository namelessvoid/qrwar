#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "engine/square.hpp"

class SquareTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(SquareTest);
	CPPUNIT_TEST(getDistanceTest);
	CPPUNIT_TEST_SUITE_END();

	public:
		void setUp()
		{
			sq1 = new qrw::Square();
			sq2 = new qrw::Square();
		}

		void tearDown()
		{
			delete sq1;
			delete sq2;
		}

		void getDistanceTest()
		{
			sq1->setPosition(0, 0);
			sq2->setPosition(0, 0);
			CPPUNIT_ASSERT(sq1->getDistance(sq2) == 0);

			sq2->setPosition(0, 1);
			CPPUNIT_ASSERT(sq1->getDistance(sq2) == 1);

			sq2->setPosition(1, 0);
			CPPUNIT_ASSERT(sq1->getDistance(sq2) == 1);

			sq2->setPosition(1, 1);
			CPPUNIT_ASSERT(sq1->getDistance(sq2) == 2);

			sq2->setPosition(2, 1);
			CPPUNIT_ASSERT(sq1->getDistance(sq2) == 3);

			sq2->setPosition(2, 0);
			CPPUNIT_ASSERT(sq1->getDistance(sq2) == 2);

			sq2->setPosition(-2, 1);
			CPPUNIT_ASSERT(sq2->getDistance(sq1) == 3);
		}

	private:
		qrw::Square* sq1;
		qrw::Square* sq2;
};

CPPUNIT_TEST_SUITE_REGISTRATION(SquareTest);