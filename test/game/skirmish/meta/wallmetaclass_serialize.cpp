#include <gtest/gtest.h>

#include "game/skirmish/meta/wallmetaclass.hpp"
#include "game/skirmish/meta/coordinatemetaclass.hpp"

#include "game/skirmish/wall.hpp"
#include "meta/metamanager.hpp"

TEST(WallMetaClass_Serialize, Then_all_properties_are_included)
{
	// Arrange
	qrw::MetaManager metaManager;
	metaManager.registerMetaClass<qrw::CoordinateMetaClass>(qrw::Coordinates::typeName);

	qrw::WallMetaClass wallMetaClass(metaManager);

	qrw::Wall wall;
	wall.setPosition({1, 2});

	YAML::Emitter out;

	// Act
	wallMetaClass.serialize(&wall, out);

	// Assert
	std::string yaml = out.c_str();
	YAML::Node result = YAML::Load(out.c_str());

	ASSERT_TRUE(result["position_"]) << "Key 'position_' does not exist";
	ASSERT_TRUE(result["position_"]["_x"]) << "Key 'position_._x does not exist";
	ASSERT_TRUE(result["position_"]["_y"]) << "Key 'position_._y does not exist";
	ASSERT_TRUE(result[qrw::MetaClass::TYPE_NAME_YAML_KEY]) << "Key '" << qrw::MetaClass::TYPE_NAME_YAML_KEY << "' does not exist";

	EXPECT_EQ(result["position_"]["_x"].as<int>(), 1);
	EXPECT_EQ(result["position_"]["_y"].as<int>(), 2);
	EXPECT_EQ(result[qrw::MetaClass::TYPE_NAME_YAML_KEY].as<std::string>(), qrw::Wall::typeName.getStringId());
}