#include "../src/util/multicast_delegate.h"

#include "gtest/gtest.h"

using namespace nexus;

TEST(one_shot_event, construct_empty) {
	test::one_shot_event<void()> event;
	EXPECT_TRUE(event.empty());
}

TEST(one_shot_event, construct_void_lambda) {
	test::one_shot_event<void(int)> event([](int) {});
}

TEST(one_shot_event, invoke_lambda) {
	test::one_shot_event<int(int)> event([](int num) { return num + 1; });
	const auto return_value = event(12);
	EXPECT_EQ(return_value, 13);
}

TEST(one_shot_event, empty) {
	test::one_shot_event<int()> event([]() { return 1; });
	EXPECT_FALSE(event.empty());
	event();
	EXPECT_TRUE(event.empty());
}

TEST(one_shot_event, bool_conversion) {
	test::one_shot_event<int()> event([]() { return 1; });
	if (!event) {
		EXPECT_FALSE()
	}
}