#include "../src/events/event_system.h"
#include "gtest/gtest.h"

using namespace nexus;

struct test_event_1 {
	int m_number;
};

TEST(event_system, register_listener) {
	event_system events;
	const auto token = events.register_listener<test_event_1>([](auto& /*event*/) {});
	EXPECT_EQ(events.listener_count<test_event_1>(), 1u);
}

TEST(event_system, post_event) {
	event_system events;
	uint32_t message_count(0);
	const auto token =
		events.register_listener<test_event_1>([&message_count](auto& /*event*/) { ++message_count; });
	EXPECT_EQ(message_count, 0u);
	events.post(test_event_1{1});
	EXPECT_EQ(message_count, 1u);
}

TEST(event_system, enqueue_event) {
	event_system events;
	uint32_t message_count(0);
	const auto token =
		events.register_listener<test_event_1>([&message_count](auto& /*event*/) { ++message_count; });
	events.enqueue(test_event_1{1});
	EXPECT_EQ(message_count, 0u);
	events.flush();
	EXPECT_EQ(message_count, 1u);
}

TEST(event_system, expired_listener_token_removes_listener) {
	event_system events;
	uint32_t message_count(0);
	{
		auto token =
			events.register_listener<test_event_1>([&message_count](auto& /*event*/) { ++message_count; });
	}
	events.post(test_event_1{1});
	EXPECT_EQ(message_count, 0u);
}

TEST(event_system, listener_token_can_be_copied) {
	event_system events;
	uint32_t message_count(0);
	{
		auto first_token =
			events.register_listener<test_event_1>([&message_count](auto& /*event*/) { ++message_count; });
		auto second_token(first_token);
	}
	events.post(test_event_1{1});
	EXPECT_EQ(message_count, 0u);
}

TEST(event_system, listener_token_can_expire_after_system) {
	auto system = std::make_unique<event_system>();
	auto first_token = system->register_listener<test_event_1>([](auto& /*event*/) {});
	system.reset();
}

TEST(event_system, invalidated_listener_token_stops_events) {
	event_system events;
	uint32_t message_count(0);
	auto token = events.register_listener<test_event_1>([&message_count](auto& /*event*/) { ++message_count; });
	auto tokenCopy(token); // even if a copy exists, invalidating the listener token will stop all events
	events.post(test_event_1{1});
	EXPECT_EQ(message_count, 1u);
	token.invalidate();
	events.post(test_event_1{1});
	EXPECT_EQ(message_count, 1u);
}