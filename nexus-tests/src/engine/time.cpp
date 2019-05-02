#include "gtest/gtest.h"
#include "../src/time.h"

TEST(clock, time_conversion) {
	nexus::time sample_time{std::chrono::seconds(62)};
	EXPECT_EQ(sample_time.as_seconds(), 62.0f);
	EXPECT_EQ(sample_time.as_milliseconds(), 62000u);
	EXPECT_EQ(sample_time.as_minutes(), 1u);
}

TEST(clock, elapsed_time) {
	nexus::clock clock;
	const auto sleep_time = std::chrono::milliseconds(10);
	std::this_thread::sleep_for(sleep_time);
	EXPECT_GE(clock.elapsed_time().as_duration(), sleep_time);
}

TEST(clock, reset) {
	nexus::clock clock;
	const auto sleep_time = std::chrono::milliseconds(10);
	std::this_thread::sleep_for(sleep_time);
	const auto duration_1 = clock.reset().as_milliseconds();
	std::this_thread::sleep_for(sleep_time);
	const auto duration_2 = clock.reset().as_milliseconds();
	const auto difference = std::max(duration_1, duration_2) - std::min(duration_1, duration_2);
	EXPECT_LE(difference, 1);
}