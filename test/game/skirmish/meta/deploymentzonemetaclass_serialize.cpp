#include <gtest/gtest.h>

#include "meta/metamanager.hpp"

#include "game/deploymentzone.hpp"
#include "game/skirmish/meta/deploymentzonemetaclass.hpp"

TEST(DeploymentZoneMetaClass_Serialize, Then_all_properties_are_included)
{
	// Arrange
	qrw::DeploymentZone deploymentZone;
	deploymentZone.setPlayerId(2);
	deploymentZone.addSquare({4, 5});
	deploymentZone.addSquare({10, 11});

	qrw::MetaManager metaManager;
	qrw::DeploymentZoneMetaClass deploymentZoneMetaClass(metaManager);

	YAML::Emitter out;

	// Act
	deploymentZoneMetaClass.serialize(&deploymentZone, out);

	// Assert
	YAML::Node result = YAML::Load(out.c_str());
	ASSERT_TRUE(result["playerId"]) << "Key 'playerId' does not exist";
	ASSERT_TRUE(result["zone_"]) << "Key 'zone_' does not exist";

	EXPECT_EQ(result["zone_"].size(), 2);

	ASSERT_TRUE(result["zone_"][0]) << "Key 'zone_.0' does not exist";
	ASSERT_TRUE(result["zone_"][0]["x"]) << "Key 'zone_.0.x' does not exist";
	ASSERT_TRUE(result["zone_"][0]["y"]) << "Key 'zone_.0.y' does not exist";

	ASSERT_TRUE(result["zone_"][1]) << "Key 'zone_.1' does not exist";
	ASSERT_TRUE(result["zone_"][1]["x"]) << "Key 'zone_.1.x' does not exist";
	ASSERT_TRUE(result["zone_"][1]["y"]) << "Key 'zone_.1.y' does not exist";

	EXPECT_EQ(result["zone_"][0]["x"].as<int>(), 4);
	EXPECT_EQ(result["zone_"][0]["y"].as<int>(), 5);
	EXPECT_EQ(result["zone_"][1]["x"].as<int>(), 10);
	EXPECT_EQ(result["zone_"][1]["y"].as<int>(), 11);
}