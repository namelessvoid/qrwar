#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "engine/unit.hpp"
#include "engine/square.hpp"

class UnitTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(UnitTest);
	CPPUNIT_TEST(attackTest);
	CPPUNIT_TEST(setGetSquareTest);
	CPPUNIT_TEST_SUITE_END();

	public:
		void setUp()
		{
			unit1 = new qrw::Unit(qrw::EUT_SWORDMAN, 5, 2, 1, 0, 0, 0);
			unit2 = new qrw::Unit(qrw::EUT_SWORDMAN, 5, 3, 1, 0, 0, 0);
		}

		void tearDown()
		{
			delete unit1;
			delete unit2;
		}

		void attackTest()
		{
			int mods[] = {0, 0};
			unit1->attack(unit2, mods, mods);
			CPPUNIT_ASSERT(unit1->getHP() == 3);
			CPPUNIT_ASSERT(unit2->getHP() == 4);
			unit2->attack(unit1, mods, mods);
			CPPUNIT_ASSERT(unit1->getHP() == 1);
			CPPUNIT_ASSERT(unit2->getHP() == 3);
			unit2->attack(unit1, mods, mods);
			CPPUNIT_ASSERT(unit1->getHP() == 0);
			CPPUNIT_ASSERT(unit2->getHP() == 3);
		}

		void setGetSquareTest()
		{
			qrw::Square square(1, 2);

			unit1->setSquare(&square);

			CPPUNIT_ASSERT(&square == unit1->getSquare());
		}

	private:
		qrw::Unit* unit1;
		qrw::Unit* unit2;
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest);
