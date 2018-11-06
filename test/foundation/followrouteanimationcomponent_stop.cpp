#include <gtest/gtest.h>

#include "foundation/followrouteanimationcomponent.hpp"

#include "rendering/renderable.hpp"

TEST(FollowRouteAnimationComponent_Stop, Then_corners_are_reset)
{
	// Arrange
	class RenderableMock : public qrw::Renderable
	{
	public:
		RenderableMock() : Renderable(0) {}
		void setPosition(const sf::Vector2f& position) { setPositionCalls.push_back(position); }
		std::vector<sf::Vector2f> setPositionCalls;

		void render(sf::RenderTarget& renderTarget) override {}
		const sf::Vector2f& getPosition() const override { throw "Not Implemented"; }
	};
	RenderableMock renderableMock;

	qrw::FollowRouteAnimationComponent followRouteAnimationComponent(&renderableMock);
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
	ASSERT_EQ(renderableMock.setPositionCalls.size(), 1);
	EXPECT_EQ(renderableMock.setPositionCalls[0], sf::Vector2f(9, 9));
}