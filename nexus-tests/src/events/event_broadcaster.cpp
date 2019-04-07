#include "../src/events/event_broadcaster.h"
#include "../include/nexus/nexus.h"

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

TEST(event_system, expired_cancel_token_removes_listener) {
	event_system events;
	uint32_t message_count(0);
	{
		auto token =
			events.register_listener<test_event_1>([&message_count](auto& /*event*/) { ++message_count; });
	}
	events.post(test_event_1{1});
	EXPECT_EQ(message_count, 0u);
}

TEST(event_system, cancel_token_can_be_copied) {
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

TEST(event_system, cancel_token_can_expire_after_system) {
	auto system = std::make_unique<event_system>();
	uint32_t message_count(0);
	{
		auto first_token =
			system->register_listener<test_event_1>([&message_count](auto& /*event*/) { ++message_count; });
		system.reset();

		event_system::listener test = first_token;
		event_system::listener test2(test);
	}
}

/*
TEST(event_broadcaster, remove_listener) {
	event_system broadcaster;
	auto listener = std::make_shared<test_listener>();
	broadcaster.register_listener<test_event_1>(listener);
	EXPECT_EQ(broadcaster.listener_count<test_event_1>(), 1u);
	broadcaster.remove_listener<test_event_1>(listener);
	EXPECT_EQ(broadcaster.listener_count<test_event_1>(), 0u);
}

TEST(event_broadcaster, post_event) {
	event_system broadcaster;
	auto listener = std::make_shared<test_listener>();
	broadcaster.register_listener<test_event_1>(listener);
	broadcaster.register_listener<test_event_2>(listener);
	EXPECT_EQ(listener->m_numbers.size(), 0u);
	EXPECT_EQ(listener->m_strings.size(), 0u);
	broadcaster.post(test_event_1{1});
	broadcaster.post(test_event_1{1});
	broadcaster.post(test_event_2{"test"});
	EXPECT_EQ(listener->m_numbers.size(), 2u);
	EXPECT_EQ(listener->m_strings.size(), 1u);
}

TEST(event_broadcaster, enqueue_event) {
	event_system broadcaster;
	auto listener = std::make_shared<test_listener>();
	broadcaster.register_listener<test_event_1>(listener);
	broadcaster.register_listener<test_event_2>(listener);
	broadcaster.enqueue(test_event_1{1});
	broadcaster.enqueue(test_event_1{1});
	broadcaster.enqueue(test_event_2{"test"});
	EXPECT_EQ(listener->m_numbers.size(), 0u);
	EXPECT_EQ(listener->m_strings.size(), 0u);
	broadcaster.flush();
	EXPECT_EQ(listener->m_numbers.size(), 2u);
	EXPECT_EQ(listener->m_strings.size(), 1u);
}
*/