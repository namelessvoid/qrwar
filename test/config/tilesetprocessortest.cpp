#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "config/tilesetprocessor.hpp"

class TilesetProcessorTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TilesetProcessorTest);
	CPPUNIT_TEST(loadTilesetTest);
	CPPUNIT_TEST_SUITE_END();

	public:
		void setUp()
		{
			tp = new qrw::TilesetProcessor();
		}

		void loadTilesetTest()
		{
			CPPUNIT_ASSERT(tp->loadTileset("./res/defaulttileset.xml") == 0);
		}

		void tearDown()
		{
			delete tp;
		}

	private:
		qrw::TilesetProcessor* tp;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TilesetProcessorTest);