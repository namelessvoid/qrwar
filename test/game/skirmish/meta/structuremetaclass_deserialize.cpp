#include <gtest/gtest.h>
#include <game/skirmish/meta/coordinatemetaclass.hpp>

#include "game/skirmish/meta/structuremetaclass.hpp"

#include "meta/metamanager.hpp"

#include "game/skirmish/structure.hpp"

TEST(StructureMetaClass_Deserialize, Then_all_properties_are_deserialized)
{
	// Arrange
	qrw::MetaManager metaManager;
	metaManager.registerMetaClass<qrw::CoordinateMetaClass>(qrw::Coordinates::typeName);
	qrw::StructureMetaClass structureMetaClass(metaManager);

	qrw::Structure structure;

	YAML::Node node;
	node["position_"]["_x"] = 12;
	node["position_"]["_y"] = 13;
	node["type_"] = 1;

	// Act
	structureMetaClass.deserialize(&structure, node);

	// Assert
	EXPECT_EQ(structure.getPosition(), qrw::Coordinates(12, 13));
}