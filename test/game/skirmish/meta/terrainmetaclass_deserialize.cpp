#include <gtest/gtest.h>

#include "game/skirmish/meta/terrainmetaclass.hpp"

#include "meta/metamanager.hpp"

#include "engine/terrain.hpp"

TEST(TerrainMetaClass_Deserialize, Then_all_properties_are_initialized)
{
	// Arrange
	YAML::Node node;
	node["type_"] = static_cast<int>(qrw::TERRAINTYPES::ET_HILL);
	node["position_"]["x_"] = 10;
	node["position_"]["y_"] = 11;

	qrw::Terrain terrain;

	qrw::MetaManager metaManager;
	qrw::TerrainMetaClass terrainMetaClass(metaManager);

	// Act
	terrainMetaClass.deserialize(&terrain, node);

	// Assert
	EXPECT_EQ(terrain.getType(), qrw::TERRAINTYPES::ET_HILL);
	EXPECT_EQ(terrain.getPosition(), qrw::Coordinates(10, 11));
}