#include <gtest/gtest.h>

#include "game/skirmish/meta/stairsmetaclass.hpp"
#include "game/skirmish/meta/coordinatemetaclass.hpp"

#include "game/skirmish/wall.hpp"
#include "meta/metamanager.hpp"

TEST(StairsMetaClass_Serialize, Then_all_properties_are_included)
{
	// Arrange
	qrw::MetaManager metaManager;
	metaManager.registerMetaClass<qrw::CoordinateMetaClass>(qrw::Coordinates::typeName);

	qrw::StairsMetaClass stairsMetaClass(metaManager);

	qrw::Stairs stairs;
	stairs.setPosition({1, 2});

	YAML::Emitter out;

	// Act
	stairsMetaClass.serialize(&stairs, out);

	// Assert
	std::string yaml = out.c_str();
	YAML::Node result = YAML::Load(out.c_str());

	ASSERT_TRUE(result["position_"]) << "Key 'position_' does not exist";
	ASSERT_TRUE(result["position_"]["_x"]) << "Key 'position_._x does not exist";
	ASSERT_TRUE(result["position_"]["_y"]) << "Key 'position_._y does not exist";
	ASSERT_TRUE(result["face_"]) << "Key 'face_' does not exist";
	ASSERT_TRUE(result["face_"]["_x"]) << "Key 'face_._x does not exist";
	ASSERT_TRUE(result["face_"]["_y"]) << "Key 'face_._y does not exist";
	ASSERT_TRUE(result[qrw::MetaClass::TYPE_NAME_YAML_KEY]) << "Key '" << qrw::MetaClass::TYPE_NAME_YAML_KEY << "' does not exist";

	EXPECT_EQ(result["position_"]["_x"].as<int>(), 1);
	EXPECT_EQ(result["position_"]["_y"].as<int>(), 2);
	EXPECT_EQ(result["face_"]["_x"].as<int>(), stairs.getFace().getX());
	EXPECT_EQ(result["face_"]["_y"].as<int>(), stairs.getFace().getY());
	EXPECT_EQ(result[qrw::MetaClass::TYPE_NAME_YAML_KEY].as<std::string>(), qrw::Stairs::typeName.getStringId());
}