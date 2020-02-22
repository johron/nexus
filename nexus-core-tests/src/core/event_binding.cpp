#include "../src/core/event_binding.h"
#include "gtest/gtest.h"

using binding_t = nexus::event_binding<int, std::function<void()>>;

TEST(event_binding, construct_default) {
	binding_t binding;
	EXPECT_EQ(binding.size(), 0u);
}

TEST(event_binding, bind_single) {
	binding_t binding;
	auto func_1 = []() { /* any callable object */ };
	binding.bind(1, func_1);
	EXPECT_EQ(binding.size(), 1u);
}

TEST(event_binding, bind_multiple) {
	binding_t binding;
	auto func_1 = []() { /* should be called first */ };
	auto func_2 = []() { /* should be called second */ };
	auto func_3 = []() { /* should be called third */ };
	binding.bind(1, func_1, func_2, func_3);
	EXPECT_EQ(binding.size(), 1u);
}

TEST(event_binding, has_binding) {
	binding_t binding;
	EXPECT_FALSE(binding.has_binding(1));
	binding.bind(1, []() {});
	EXPECT_TRUE(binding.has_binding(1));
}

TEST(event_binding, trigger) {
	binding_t binding;
	std::size_t counter = 0;
	auto func_1 = [&counter]() { EXPECT_EQ(++counter, 1); };
	auto func_2 = [&counter]() { EXPECT_EQ(++counter, 2); };
	auto func_3 = [&counter]() { EXPECT_EQ(++counter, 3); };
	binding.bind(1, func_1, func_2, func_3);
	binding.trigger(1);
	EXPECT_EQ(counter, 3u);
}

TEST(event_binding, trigger_with_args) {
	using custom_binding = nexus::event_binding<int, std::function<void(int, int)>>;
	custom_binding binding;

	binding.bind(1, [](int lhs, int rhs) { [[maybe_unused]] auto res = lhs + rhs; });
	binding.trigger(1, 2, 3);
}

TEST(event_binding, append) {
	binding_t binding;
	std::size_t counter = 0;
	auto func_1 = [&counter]() { EXPECT_EQ(++counter, 1); };
	auto func_2 = [&counter]() { EXPECT_EQ(++counter, 2); };
	binding.bind(1, func_1, func_2);
	auto func_3 = [&counter]() { EXPECT_EQ(++counter, 3); };
	binding.append(1, func_3);
	binding.trigger(1);
	EXPECT_EQ(counter, 3u);
}

TEST(event_binding, erase) {
	binding_t binding;
	binding.bind(1, []() {});
	EXPECT_TRUE(binding.has_binding(1));
	binding.erase(1);
	EXPECT_FALSE(binding.has_binding(1));
}
