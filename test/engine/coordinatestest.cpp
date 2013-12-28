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

		void testPtrComp()
		{
			qrw::Coordinates::PtrCompLess ptrcomp;

			qrw::Coordinates* coord1 = new qrw::Coordinates(0, 0);
			qrw::Coordinates* coord2 = new qrw::Coordinates(0, 0);

			// 1: (0/0), 2: (0/0)
			CPPUNIT_ASSERT(ptrcomp(coord1, coord2) == false);
			CPPUNIT_ASSERT(ptrcomp(coord2, coord1) == false);

			// 1: (0/0), 2: (1/0)
			coord2->setX(1);
			CPPUNIT_ASSERT(ptrcomp(coord1, coord2) == true);
			CPPUNIT_ASSERT(ptrcomp(coord2, coord1) == false);

			// 1: (0/4), 2: (1/0)
			coord1->setY(4);
			CPPUNIT_ASSERT(ptrcomp(coord1, coord2) == true);
			CPPUNIT_ASSERT(ptrcomp(coord2, coord1) == false);

			// 1: (1/4), 2: (1/0)
			coord1->setX(1);
			CPPUNIT_ASSERT(ptrcomp(coord1, coord2) == false);
			CPPUNIT_ASSERT(ptrcomp(coord2, coord1) == true);
		}

		void testSetCompatibility()
		{
			std::set<qrw::Coordinates*, qrw::Coordinates::PtrCompLess> set;

			qrw::Coordinates* coord1 = new qrw::Coordinates(0, 0);
			qrw::Coordinates* coord2 = new qrw::Coordinates(0, 0);

			set.insert(coord1);
			set.insert(coord2);

			CPPUNIT_ASSERT(set.size() == 1);

			coord2->setX(1);
			set.insert(coord2);

			CPPUNIT_ASSERT(set.size() == 2);

			CPPUNIT_ASSERT(set.find(coord1) != set.end());
			CPPUNIT_ASSERT(set.find(coord2) != set.end());

			coord2->setY(2);
			CPPUNIT_ASSERT(set.find(coord2) != set.end());

			set.insert(coord2);
			CPPUNIT_ASSERT(set.size() == 2);
		}
};

CPPUNIT_TEST_SUITE_REGISTRATION(CoordinatesTest);
