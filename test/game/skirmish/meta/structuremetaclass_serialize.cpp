#include <gtest/gtest.h>

#include "game/skirmish/meta/structuremetaclass.hpp"
#include "game/skirmish/meta/coordinatemetaclass.hpp"

#include "game/skirmish/structure.hpp"
#include "meta/metamanager.hpp"

TEST(StructureMetaClass_Serialize, Then_all_properties_are_included)
{
	// Arrange
	qrw::MetaManager metaManager;
	metaManager.registerMetaClass<qrw::CoordinateMetaClass>(qrw::Coordinates::typeName);

	qrw::StructureMetaClass structureMetaClass(metaManager);

	qrw::Structure structure;
	structure.setPosition({1, 2});

	YAML::Emitter out;

	// Act
	structureMetaClass.serialize(&structure, out);

	// Assert
	std::string yaml = out.c_str();
	YAML::Node result = YAML::Load(out.c_str());

	ASSERT_TRUE(result["position_"]) << "Key 'position_' does not exist";
	ASSERT_TRUE(result["position_"]["_x"]) << "Key 'position_._x does not exist";
	ASSERT_TRUE(result["position_"]["_y"]) << "Key 'position_._y does not exist";
	ASSERT_TRUE(result["type_"]) << "Key 'type_' does not exist";

	EXPECT_EQ(result["position_"]["_x"].as<int>(), 1);
	EXPECT_EQ(result["position_"]["_y"].as<int>(), 2);
	EXPECT_EQ(result["type_"].as<unsigned int>(), 0);
}