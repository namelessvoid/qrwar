#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "engine/unit.hpp"

class UnitTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(UnitTest);
	CPPUNIT_TEST(attackTest);
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
			unit1->attack(unit2);
			CPPUNIT_ASSERT(unit1->getHP() == 3);
			CPPUNIT_ASSERT(unit2->getHP() == 4);
			unit2->attack(unit1);
			CPPUNIT_ASSERT(unit1->getHP() == 1);
			CPPUNIT_ASSERT(unit2->getHP() == 3);
			unit2->attack(unit1);
			CPPUNIT_ASSERT(unit1->getHP() == 0);
			CPPUNIT_ASSERT(unit2->getHP() == 3);
		}

	private:
		qrw::Unit* unit1;
		qrw::Unit* unit2;
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest);