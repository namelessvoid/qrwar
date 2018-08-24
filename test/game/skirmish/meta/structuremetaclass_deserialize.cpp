#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "game/skirmish/meta/coordinatemetaclass.hpp"
#include "game/skirmish/meta/structuremetaclass.hpp"

#include "meta/metamanager.hpp"

#include "game/skirmish/structure.hpp"

using ::testing::NotNull;

TEST(StructureMetaClass_Deserialize, Then_all_properties_are_deserialized)
{
	// Arrange
	qrw::MetaManager metaManager;
	metaManager.registerMetaClass<qrw::CoordinateMetaClass>(qrw::Coordinates::typeName);
	qrw::StructureMetaClass structureMetaClass(metaManager);

	YAML::Node node;
	node["position_"]["_x"] = 12;
	node["position_"]["_y"] = 13;
	node["type_"] = 1;

	// Act
	qrw::Structure* structure = dynamic_cast<qrw::Structure*>(structureMetaClass.deserialize(node));

	// Assert
	ASSERT_THAT(structure, NotNull());
	EXPECT_EQ(structure->getPosition(), qrw::Coordinates(12, 13));

	delete structure;
}