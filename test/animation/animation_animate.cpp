#include <gtest/gtest.h>

#include "animation/animation.hpp"

TEST(Animation_Animate, If_started_Then_it_animates)
{
	// Arrange
	qrw::Animation animation;
	animation.setDuration(1);

	// Act
	animation.start();
	animation.animate(0.5);

	// Assert
	EXPECT_EQ(animation.getCurrentRunTime(), 0.5);

}

TEST(Animation_Animate, If_not_started_Then_nothing_is_animated)
{
	// Arrange
	qrw::Animation animation;
	animation.setDuration(1);

	// Act
	animation.animate(0.5);

	// Assert
	EXPECT_EQ(animation.getCurrentRunTime(), 0);
}

TEST(Animation_Animate, If_delta_time_exceeds_end_Then_current_run_time_clamps_to_duration)
{
	// Arrange
	qrw::Animation animation;
	animation.setDuration(1);
	animation.start();

	// Act
	animation.animate(10);

	// Assert
	EXPECT_EQ(animation.getCurrentRunTime(), 1);
}

TEST(Animation_Animate, If_duration_is_reached_Then_animation_is_stopped_not_before_next_animate_call)
{
	// Arrange
	qrw::Animation animation;
	animation.setDuration(1);
	animation.start();

	// Act
	animation.animate(10);

	// Assert
	EXPECT_TRUE(animation.isRunning());

	// Act
	animation.animate(1);

	// Assert
	EXPECT_FALSE(animation.isRunning());
}