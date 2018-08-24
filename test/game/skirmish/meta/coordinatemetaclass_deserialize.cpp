#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "meta/metamanager.hpp"
#include "game/skirmish/meta/coordinatemetaclass.hpp"

class CoordinateMetaClass_Deserialize : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(CoordinateMetaClass_Deserialize);
	CPPUNIT_TEST(Then_x_and_y_are_deserialized);
	CPPUNIT_TEST_SUITE_END();

public:
	void Then_x_and_y_are_deserialized()
	{
		qrw::MetaManager metaManager;
		qrw::CoordinateMetaClass metaClass(metaManager);
		YAML::Node node;
		node["_x"] = 12;
		node["_y"] = 13;

		auto coordinate = dynamic_cast<qrw::Coordinates*>(metaClass.deserialize(node));

		CPPUNIT_ASSERT(coordinate != nullptr);
		CPPUNIT_ASSERT_EQUAL(12, coordinate->getX());
		CPPUNIT_ASSERT_EQUAL(13, coordinate->getY());

		delete coordinate;
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(CoordinateMetaClass_Deserialize);