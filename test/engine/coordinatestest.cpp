#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include <set>

#include "engine/coordinates.hpp"

class CoordinatesTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(CoordinatesTest);
	CPPUNIT_TEST(test);
	CPPUNIT_TEST(testPtrComp);
	CPPUNIT_TEST(testSetCompatibility);
	CPPUNIT_TEST(testCopyCtor);
	CPPUNIT_TEST(testOperatorEquals);
	CPPUNIT_TEST(testOperatorPlus);
	CPPUNIT_TEST(testOperatorMinus);
	CPPUNIT_TEST_SUITE_END();

	public:
		void setUp()
		{
			coord0_0   = new qrw::Coordinates(0, 0);
			coord0_0_2 = new qrw::Coordinates(0, 0);
			coord1_0   = new qrw::Coordinates(1, 0);
			coord0_4   = new qrw::Coordinates(0, 4);
			coord1_4   = new qrw::Coordinates(1, 4);
		}

		void tearDown()
		{
			delete coord0_0;
			delete coord0_0_2;
			delete coord1_0;
			delete coord0_4;
			delete coord1_4;
		}

		void test()
		{
			qrw::Coordinates coord1(3);

			CPPUNIT_ASSERT(coord1.getX() == 3);
			CPPUNIT_ASSERT(coord1.getY() == 0);

			qrw::Coordinates coord2(0, 12);
			CPPUNIT_ASSERT(coord2.getX() == 0);
			CPPUNIT_ASSERT(coord2.getY() == 12);

			qrw::Coordinates coord3(4, 12);
			CPPUNIT_ASSERT(coord3.getX() == 4);
			CPPUNIT_ASSERT(coord3.getY() == 12);
		}

		void testPtrComp()
		{
			qrw::Coordinates::PtrCompLess ptrcomp;

			// 1: (0/0), 2: (0/0)
			CPPUNIT_ASSERT(ptrcomp(coord0_0, coord0_0_2) == false);
			CPPUNIT_ASSERT(ptrcomp(coord0_0_2, coord0_0) == false);

			// 1: (0/0), 2: (1/0)
			CPPUNIT_ASSERT(ptrcomp(coord0_0, coord1_0) == true);
			CPPUNIT_ASSERT(ptrcomp(coord1_0, coord0_0) == false);

			// 1: (0/4), 2: (1/0)
			CPPUNIT_ASSERT(ptrcomp(coord0_4, coord1_0) == true);
			CPPUNIT_ASSERT(ptrcomp(coord1_0, coord0_4) == false);

			// 1: (1/4), 2: (1/0)
			CPPUNIT_ASSERT(ptrcomp(coord1_4, coord1_0) == false);
			CPPUNIT_ASSERT(ptrcomp(coord1_0, coord1_4) == true);
		}

		void testSetCompatibility()
		{
			std::set<qrw::Coordinates*, qrw::Coordinates::PtrCompLess> set;

			set.insert(coord0_0);
			set.insert(coord0_0_2);

			CPPUNIT_ASSERT(set.size() == 1);

			set.insert(coord1_0);

			CPPUNIT_ASSERT(set.size() == 2);

			CPPUNIT_ASSERT(set.find(coord0_0) != set.end());
			CPPUNIT_ASSERT(set.find(coord1_0) != set.end());
		}

		void testCopyCtor()
		{
			qrw::Coordinates* copy = new qrw::Coordinates(*coord0_4);

			CPPUNIT_ASSERT(copy != coord0_4);
			CPPUNIT_ASSERT(copy->getX() == coord0_4->getX());
			CPPUNIT_ASSERT(copy->getY() == coord0_4->getY());

			delete copy;
		}

		void testOperatorEquals()
		{
			CPPUNIT_ASSERT(*coord0_0 == *coord0_0_2);
			CPPUNIT_ASSERT((*coord0_0 == *coord1_4) == false);
		}

		void testOperatorPlus()
		{
			qrw::Coordinates* coords = new qrw::Coordinates(*coord1_0 + *coord1_4);

			CPPUNIT_ASSERT(coords->getX() == 2);
			CPPUNIT_ASSERT(coords->getY() == 4);

			delete coords;
		}

		void testOperatorMinus()
		{
			qrw::Coordinates coords(*coord0_0 - *coord1_4);

			CPPUNIT_ASSERT(coords.getX() == -1);
			CPPUNIT_ASSERT(coords.getY() == -4);
		}

	private:
		qrw::Coordinates* coord0_0;
		qrw::Coordinates* coord0_0_2;
		qrw::Coordinates* coord1_0;
		qrw::Coordinates* coord0_4;
		qrw::Coordinates* coord1_4;
};

CPPUNIT_TEST_SUITE_REGISTRATION(CoordinatesTest);
