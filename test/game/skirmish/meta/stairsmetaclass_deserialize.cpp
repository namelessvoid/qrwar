#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "game/skirmish/meta/stairsmetaclass.hpp"

#include "game/skirmish/meta/coordinatemetaclass.hpp"
#include "game/skirmish/meta/structuremetaclass.hpp"

#include "meta/metamanager.hpp"

using ::testing::NotNull;

TEST(StairsMetaClass_Deserialize, Then_all_properties_are_deserialized)
{
	// Arrange
	qrw::MetaManager metaManager;
	metaManager.registerMetaClass<qrw::CoordinateMetaClass>(qrw::Coordinates::typeName);
	qrw::StairsMetaClass stairsMetaClass(metaManager);

	YAML::Node node;
	node["position_"]["_x"] = 12;
	node["position_"]["_y"] = 13;
	node["face_"]["_x"] = 1;
	node["face_"]["_y"] = 0;

	// Act
	qrw::Stairs* structure = dynamic_cast<qrw::Stairs*>(stairsMetaClass.deserialize(node));

	// Assert
	ASSERT_THAT(structure, NotNull());
	EXPECT_EQ(structure->getPosition(), qrw::Coordinates(12, 13));
	EXPECT_EQ(structure->getFace(), qrw::Directions::EAST);

	delete structure;
}