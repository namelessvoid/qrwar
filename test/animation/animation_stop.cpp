#include <gtest/gtest.h>

#include "animation/animation.hpp"

TEST(Animation_Stop, Then_current_run_time_is_reset)
{
	qrw::Animation animation;
	animation.setDuration(1);
	animation.start();
	animation.animate(0.5);

	EXPECT_EQ(animation.getCurrentRunTime(), 0.5);

	// Act
	animation.stop();

	// Assert
	EXPECT_EQ(animation.getCurrentRunTime(), 0);
}