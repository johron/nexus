#include "gtest/gtest.h"
#include "../src/time.h"

TEST(timer, time_conversion) {
	nexus::time sample_time{std::chrono::seconds(62)};
	EXPECT_EQ(sample_time.as_seconds(), 62.0f);
	EXPECT_EQ(sample_time.as_milliseconds(), 62000u);
	EXPECT_EQ(sample_time.as_minutes(), 1);
}

TEST(timer, elapsed_time) {
	nexus::timer timer;
	const auto sleep_time = std::chrono::milliseconds(10);
	std::this_thread::sleep_for(sleep_time);
	EXPECT_GE(timer.elapsed_time().as_duration(), sleep_time);
}

/*
TEST(timer, reset) {
	nexus::timer timer;
	const auto sleep_time = std::chrono::milliseconds(10);
	std::this_thread::sleep_for(sleep_time);
	const auto duration_1 = timer.reset().as_milliseconds();
	std::this_thread::sleep_for(sleep_time);
	const auto duration_2 = timer.reset().as_milliseconds();
	const auto difference = std::max(duration_1, duration_2) - std::min(duration_1, duration_2);
	EXPECT_LE(difference, 3);
}
*/
