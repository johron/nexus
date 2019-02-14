#include "gtest/gtest.h"
#include "nexus/nexus-lib.h"

auto make_input_handler() {
	return nexus::input_handler<char>();
}

TEST(input_handler, bind_and_trigger) {
	auto handler = make_input_handler();
	bool has_been_triggered(false);
	auto trigger = [&has_been_triggered]() { has_been_triggered = true; };
	handler.bind('a', trigger);
	EXPECT_FALSE(has_been_triggered);
	handler.trigger('b');
	EXPECT_FALSE(has_been_triggered);
	handler.trigger('a');
	EXPECT_TRUE(has_been_triggered);
}

TEST(input_handler, has_binding) {
	auto handler = make_input_handler();
	EXPECT_FALSE(handler.has_binding('a'));
	handler.bind('a', []() {});
	EXPECT_TRUE(handler.has_binding('a'));
}

TEST(input_handler, clear_binding) {
	auto handler = make_input_handler();
	handler.bind('a', []() {});
	EXPECT_TRUE(handler.has_binding('a'));
	handler.clear('a');
	EXPECT_FALSE(handler.has_binding('a'));
}
