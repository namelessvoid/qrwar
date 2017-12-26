#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "engine/unit.hpp"
#include "engine/board.hpp"
#include "engine/player.hpp"
#include "engine/terrain.hpp"
#include "engine/coordinates.hpp"

class UnitTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(UnitTest);
	CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest);
