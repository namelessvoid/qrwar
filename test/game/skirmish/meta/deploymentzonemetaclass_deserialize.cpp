#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "meta/metamanager.hpp"

#include "game/skirmish/meta/deploymentzonemetaclass.hpp"
#include "game/deploymentzone.hpp"

using ::testing::NotNull;

TEST(DeploymentZoneMetaClass_Deserialize, Then_all_properties_are_initialized)
{
	// Arrange
	YAML::Node node;
	node["type"] = qrw::DeploymentZone::typeName.getStringId();
	node["playerId"] = 2;
	node["zone_"][0]["x"] = 11;
	node["zone_"][0]["y"] = 12;
	node["zone_"][1]["x"] = 4;
	node["zone_"][1]["y"] = 5;

	qrw::MetaManager metaManager;
	qrw::DeploymentZoneMetaClass deploymentZoneMetaClass(metaManager);

	// Act
	qrw::DeploymentZone* deploymentZone = dynamic_cast<qrw::DeploymentZone*>(deploymentZoneMetaClass.deserialize(node));

	// Assert
	ASSERT_THAT(deploymentZone, NotNull());

	EXPECT_EQ(deploymentZone->getPlayerId(), 2);
	EXPECT_EQ(deploymentZone->getSize(), 2);
	EXPECT_TRUE(deploymentZone->containsSquare({11, 12}));
	EXPECT_TRUE(deploymentZone->containsSquare({4, 5}));

	delete deploymentZone;
}