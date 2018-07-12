#include <gtest/gtest.h>

#include "game/meta/terrainmetaclass.hpp"

#include "meta/metamanager.hpp"

#include "engine/terrain.hpp"

TEST(TerrainMetaClass_Serialize, Then_yaml_contains_all_properties)
{
	// Arrange
	std::unique_ptr<qrw::Terrain> terrain(qrw::Terrain::createTerrain(qrw::TERRAINTYPES::ET_WALL));
	terrain->setPosition({10, 11});

	qrw::MetaManager metaManager;
	qrw::TerrainMetaClass terrainMetaClass(metaManager);

	YAML::Emitter out;

	// Act
	terrainMetaClass.serialize(terrain.get(), out);

	// Assert
	YAML::Node result = YAML::Load(out.c_str());
	ASSERT_TRUE(result["type_"]) << "Key 'type_' does not exist";
	ASSERT_TRUE(result["position_"]) << "Key 'position_' does not exist";
	ASSERT_TRUE(result["position_"]["x_"]) << "Key 'position.x_' does not exist";
	ASSERT_TRUE(result["position_"]["y_"]) << "Key 'position.y_' does not exist";

	EXPECT_EQ(result["type_"].as<int>(), static_cast<int>(terrain->getType()));
	EXPECT_EQ(result["position_"]["x_"].as<int>(), 10);
	EXPECT_EQ(result["position_"]["y_"].as<int>(), 11);
}