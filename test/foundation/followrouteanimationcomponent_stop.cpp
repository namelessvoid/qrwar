#include <gtest/gtest.h>

#include "foundation/followrouteanimationcomponent.hpp"

#include "__mocks__/game/skirmish/unitmock.hpp"

TEST(FollowRouteAnimationComponent_Stop, Then_corners_are_reset)
{
	UnitMock unitMock;

	qrw::FollowRouteAnimationComponent followRouteAnimationComponent(&unitMock);
	followRouteAnimationComponent.addCorner({10, 10});
	followRouteAnimationComponent.addCorner({20, 20});
	followRouteAnimationComponent.start();

	// Act
	followRouteAnimationComponent.stop();
	followRouteAnimationComponent.addCorner({9, 9});
	followRouteAnimationComponent.addCorner({9, 9});
	followRouteAnimationComponent.start();
	followRouteAnimationComponent.animate(0);

	// Assert
	ASSERT_EQ(unitMock.setWorldPositionCalls.size(), 1);
	EXPECT_EQ(unitMock.setWorldPositionCalls[0], sf::Vector2f(9, 9));
}