#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "meta/metamanager.hpp"
#include "game/skirmish/meta/coordinatemetaclass.hpp"

class CoordinateMetaClass_Serialize : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(CoordinateMetaClass_Serialize);
	CPPUNIT_TEST(Then_x_and_y_are_serialized);
	CPPUNIT_TEST_SUITE_END();

public:
	void Then_x_and_y_are_serialized()
	{
		qrw::MetaManager metaManager;
		qrw::CoordinateMetaClass metaClass(metaManager);
		qrw::Coordinates coordinates(12, 13);
		YAML::Emitter emitter;

		metaClass.serialize(&coordinates, emitter);

		YAML::Node result = YAML::Load(emitter.c_str());
		CPPUNIT_ASSERT_EQUAL(12, result["_x"].as<int>());
		CPPUNIT_ASSERT_EQUAL(13, result["_y"].as<int>());
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(CoordinateMetaClass_Serialize);