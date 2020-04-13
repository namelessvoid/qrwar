#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "foundation/followrouteanimationcomponent.hpp"

#include "__mocks__/game/skirmish/unitmock.hpp"

using ::testing::ElementsAre;

namespace FollowRouteAnimationComponent_Animate
{

TEST(FollowRouteAnimationComponent_Animate, If_two_corners_are_added_Then_animates_interpolates_between_them)
{
	// Arrange
	UnitMock unitMock;
	auto followRouteAnimationComponent = new qrw::FollowRouteAnimationComponent(&unitMock);
	followRouteAnimationComponent->addCorner({0.0f, 10.0f});
	followRouteAnimationComponent->addCorner({10.0f, 20.0f});
	followRouteAnimationComponent->start();

	// Act
	followRouteAnimationComponent->animate(0);
	followRouteAnimationComponent->animate(0.5);
	followRouteAnimationComponent->animate(0.5);

	// Assert
	EXPECT_EQ(unitMock.setWorldPositionCalls[0], sf::Vector2f(0, 10))
						<< "SetPosition({" << unitMock.setWorldPositionCalls[0].x << ", " << unitMock.setWorldPositionCalls[0].y << "} "
						<< "does not match expected position {0, 10}";
	EXPECT_EQ(unitMock.setWorldPositionCalls[1], sf::Vector2f(5, 15))
						<< "SetPosition({" << unitMock.setWorldPositionCalls[1].x << ", " << unitMock.setWorldPositionCalls[1].y << "} "
						<< "does not match expected position {5, 15}";
	EXPECT_EQ(unitMock.setWorldPositionCalls[2], sf::Vector2f(10, 20))
						<< "SetPosition({" << unitMock.setWorldPositionCalls[2].x << ", " << unitMock.setWorldPositionCalls[2].y << "} "
						<< "does not match expected position {10, 20}";
}

TEST(FollowRouteAnimationComponent_Animate, If_three_corners_are_added_Then_animation_interpolates_correctly)
{
	UnitMock unitMock;
	auto followRouteAnimationComponent = new qrw::FollowRouteAnimationComponent(&unitMock);
	followRouteAnimationComponent->addCorner({0.0f, 10.0f});
	followRouteAnimationComponent->addCorner({10.0f, 20.0f});
	followRouteAnimationComponent->addCorner({30.0f, 40.0f});
	followRouteAnimationComponent->start();

	// Act
	followRouteAnimationComponent->animate(0); // call 0
	followRouteAnimationComponent->animate(0.25); // call 1
	followRouteAnimationComponent->animate(0.25); // call 2
	followRouteAnimationComponent->animate(0.25); // call 3
	followRouteAnimationComponent->animate(0.25); // call 4

	EXPECT_EQ(unitMock.setWorldPositionCalls[0], sf::Vector2f(0, 10))
						<< "SetPosition({" << unitMock.setWorldPositionCalls[0].x << ", " << unitMock.setWorldPositionCalls[0].y << "} "
						<< "does not match expected position {0, 10}";
	EXPECT_EQ(unitMock.setWorldPositionCalls[1], sf::Vector2f(5, 15))
						<< "SetPosition({" << unitMock.setWorldPositionCalls[1].x << ", " << unitMock.setWorldPositionCalls[1].y << "} "
						<< "does not match expected position {5, 15}";
	EXPECT_EQ(unitMock.setWorldPositionCalls[2], sf::Vector2f(10, 20))
						<< "SetPosition({" << unitMock.setWorldPositionCalls[2].x << ", " << unitMock.setWorldPositionCalls[2].y << "} "
						<< "does not match expected position {10, 20}";
	EXPECT_EQ(unitMock.setWorldPositionCalls[3], sf::Vector2f(20, 30))
						<< "SetPosition({" << unitMock.setWorldPositionCalls[3].x << ", " << unitMock.setWorldPositionCalls[3].y << "} "
						<< "does not match expected position {20, 30}";
	EXPECT_EQ(unitMock.setWorldPositionCalls[4], sf::Vector2f(30, 40))
						<< "SetPosition({" << unitMock.setWorldPositionCalls[4].x << ", " << unitMock.setWorldPositionCalls[4].y << "} "
						<< "does not match expected position {30, 40}";
}

TEST(FollowRouteAnimationComponent_Animate, If_time_step_is_not_one_Then_animation_interpolates_correctly)
{
	// Arrange
	UnitMock unitMock;
	auto followRouteAnimationComponent = new qrw::FollowRouteAnimationComponent(&unitMock);
	followRouteAnimationComponent->setDuration(0.5);
	followRouteAnimationComponent->addCorner({0.0f, 10.0f});
	followRouteAnimationComponent->addCorner({10.0f, 20.0f});
	followRouteAnimationComponent->start();

	// Act
	followRouteAnimationComponent->animate(0);
	followRouteAnimationComponent->animate(0.25);
	followRouteAnimationComponent->animate(0.25);

	// Assert
	EXPECT_EQ(unitMock.setWorldPositionCalls[0], sf::Vector2f(0, 10))
						<< "SetPosition({" << unitMock.setWorldPositionCalls[0].x << ", " << unitMock.setWorldPositionCalls[0].y << "} "
						<< "does not match expected position {0, 10}";
	EXPECT_EQ(unitMock.setWorldPositionCalls[1], sf::Vector2f(5, 15))
						<< "SetPosition({" << unitMock.setWorldPositionCalls[1].x << ", " << unitMock.setWorldPositionCalls[1].y << "} "
						<< "does not match expected position {5, 15}";
	EXPECT_EQ(unitMock.setWorldPositionCalls[2], sf::Vector2f(10, 20))
						<< "SetPosition({" << unitMock.setWorldPositionCalls[2].x << ", " << unitMock.setWorldPositionCalls[2].y << "} "
						<< "does not match expected position {10, 20}";
}

TEST(FollowRouteAnimationComponent_Animate, If_not_started_Then_nothing_is_animated)
{
	// Arrange
	UnitMock unitMock;
	qrw::FollowRouteAnimationComponent followRouteAnimationComponent(&unitMock);
	followRouteAnimationComponent.addCorner({0, 0});
	followRouteAnimationComponent.addCorner({1, 1});

	// Act
	followRouteAnimationComponent.animate(1);

	// Assert
	EXPECT_EQ(unitMock.setWorldPositionCalls.size(), 0);
}

} // namespace FollowRouteAnimationComponent_Animate