#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "foundation/followrouteanimationcomponent.hpp"

#include "rendering/renderable.hpp"

using ::testing::ElementsAre;

namespace FollowRouteAnimationComponent_Animate
{

class RenderableMock : public qrw::Renderable
{
public:
	RenderableMock() : Renderable(0) {};

	void setPosition(const sf::Vector2f& position) override { setPositionCalls.push_back(position); }
	std::vector<sf::Vector2f> setPositionCalls;

	void render(sf::RenderTarget& renderTarget) override {}
	const sf::Vector2f& getPosition() const override { throw "Not Implemented"; };
};

TEST(FollowRouteAnimationComponent_Animate, If_two_corners_are_added_Then_animates_interpolates_between_them)
{
	// Arrange
	RenderableMock renderableMock;
	auto followRouteAnimationComponent = new qrw::FollowRouteAnimationComponent(&renderableMock);
	followRouteAnimationComponent->addCorner({0.0f, 10.0f});
	followRouteAnimationComponent->addCorner({10.0f, 20.0f});
	followRouteAnimationComponent->start();

	// Act
	followRouteAnimationComponent->animate(0);
	followRouteAnimationComponent->animate(0.5);
	followRouteAnimationComponent->animate(0.5);

	// Assert
	EXPECT_EQ(renderableMock.setPositionCalls[0], sf::Vector2f(0, 10))
						<< "SetPosition({" << renderableMock.setPositionCalls[0].x << ", " << renderableMock.setPositionCalls[0].y << "} "
						<< "does not match expected position {0, 10}";
	EXPECT_EQ(renderableMock.setPositionCalls[1], sf::Vector2f(5, 15))
						<< "SetPosition({" << renderableMock.setPositionCalls[1].x << ", " << renderableMock.setPositionCalls[1].y << "} "
						<< "does not match expected position {5, 15}";
	EXPECT_EQ(renderableMock.setPositionCalls[2], sf::Vector2f(10, 20))
						<< "SetPosition({" << renderableMock.setPositionCalls[2].x << ", " << renderableMock.setPositionCalls[2].y << "} "
						<< "does not match expected position {10, 20}";
}

TEST(FollowRouteAnimationComponent_Animate, If_three_corners_are_added_Then_animation_interpolates_correctly)
{
	RenderableMock renderableMock;
	auto followRouteAnimationComponent = new qrw::FollowRouteAnimationComponent(&renderableMock);
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

	EXPECT_EQ(renderableMock.setPositionCalls[0], sf::Vector2f(0, 10))
						<< "SetPosition({" << renderableMock.setPositionCalls[0].x << ", " << renderableMock.setPositionCalls[0].y << "} "
						<< "does not match expected position {0, 10}";
	EXPECT_EQ(renderableMock.setPositionCalls[1], sf::Vector2f(5, 15))
						<< "SetPosition({" << renderableMock.setPositionCalls[1].x << ", " << renderableMock.setPositionCalls[1].y << "} "
						<< "does not match expected position {5, 15}";
	EXPECT_EQ(renderableMock.setPositionCalls[2], sf::Vector2f(10, 20))
						<< "SetPosition({" << renderableMock.setPositionCalls[2].x << ", " << renderableMock.setPositionCalls[2].y << "} "
						<< "does not match expected position {10, 20}";
	EXPECT_EQ(renderableMock.setPositionCalls[3], sf::Vector2f(20, 30))
						<< "SetPosition({" << renderableMock.setPositionCalls[3].x << ", " << renderableMock.setPositionCalls[3].y << "} "
						<< "does not match expected position {20, 30}";
	EXPECT_EQ(renderableMock.setPositionCalls[4], sf::Vector2f(30, 40))
						<< "SetPosition({" << renderableMock.setPositionCalls[4].x << ", " << renderableMock.setPositionCalls[4].y << "} "
						<< "does not match expected position {30, 40}";
}

TEST(FollowRouteAnimationComponent_Animate, If_time_step_is_not_one_Then_animation_interpolates_correctly)
{
	// Arrange
	RenderableMock renderableMock;
	auto followRouteAnimationComponent = new qrw::FollowRouteAnimationComponent(&renderableMock);
	followRouteAnimationComponent->setDuration(0.5);
	followRouteAnimationComponent->addCorner({0.0f, 10.0f});
	followRouteAnimationComponent->addCorner({10.0f, 20.0f});
	followRouteAnimationComponent->start();

	// Act
	followRouteAnimationComponent->animate(0);
	followRouteAnimationComponent->animate(0.25);
	followRouteAnimationComponent->animate(0.25);

	// Assert
	EXPECT_EQ(renderableMock.setPositionCalls[0], sf::Vector2f(0, 10))
						<< "SetPosition({" << renderableMock.setPositionCalls[0].x << ", " << renderableMock.setPositionCalls[0].y << "} "
						<< "does not match expected position {0, 10}";
	EXPECT_EQ(renderableMock.setPositionCalls[1], sf::Vector2f(5, 15))
						<< "SetPosition({" << renderableMock.setPositionCalls[1].x << ", " << renderableMock.setPositionCalls[1].y << "} "
						<< "does not match expected position {5, 15}";
	EXPECT_EQ(renderableMock.setPositionCalls[2], sf::Vector2f(10, 20))
						<< "SetPosition({" << renderableMock.setPositionCalls[2].x << ", " << renderableMock.setPositionCalls[2].y << "} "
						<< "does not match expected position {10, 20}";
}

TEST(FollowRouteAnimationComponent_Animate, If_not_started_Then_nothing_is_animated)
{
	// Arrange
	RenderableMock renderableMock;
	qrw::FollowRouteAnimationComponent followRouteAnimationComponent(&renderableMock);
	followRouteAnimationComponent.addCorner({0, 0});
	followRouteAnimationComponent.addCorner({1, 1});

	// Act
	followRouteAnimationComponent.animate(1);

	// Assert
	EXPECT_EQ(renderableMock.setPositionCalls.size(), 0);
}

} // namespace FollowRouteAnimationComponent_Animate