#include "../src/event_broker.h"
#include "gtest/gtest.h"

using namespace nexus;

struct test_event {
	int m_number;
};
struct test_listener {
	uint32_t m_msg_count = 0;
	void on_event(const test_event&) {
		++m_msg_count;
	}
};

TEST(event_broker, register_listener_func) {
	event_broker broker;
	const auto token = broker.register_listener<test_event>([](auto& /*event*/) {});
	EXPECT_EQ(broker.listener_count<test_event>(), 1u);
}

TEST(event_broker, register_listener_object) {
	event_broker broker;
	test_listener listener;
	const auto token = broker.register_listener<test_event>(&test_listener::on_event, &listener);
	EXPECT_EQ(broker.listener_count<test_event>(), 1u);
}

TEST(event_broker, publish_event_to_func) {
	event_broker broker;
	uint32_t message_count(0);
	const auto token =
		broker.register_listener<test_event>([&message_count](auto& /*event*/) { ++message_count; });
	EXPECT_EQ(message_count, 0u);
	broker.publish(test_event{1});
	EXPECT_EQ(message_count, 1u);
}

TEST(event_broker, publish_event_to_object) {
	event_broker broker;
	test_listener listener;
	const auto token = broker.register_listener<test_event>(&test_listener::on_event, &listener);
	EXPECT_EQ(broker.listener_count<test_event>(), 1u);
	EXPECT_EQ(listener.m_msg_count, 0u);
	broker.publish(test_event{});
	EXPECT_EQ(listener.m_msg_count, 1u);
}

TEST(event_broker, enqueue_event) {
	event_broker broker;
	uint32_t message_count(0);
	const auto token =
		broker.register_listener<test_event>([&message_count](auto& /*event*/) { ++message_count; });
	broker.enqueue(test_event{1});
	EXPECT_EQ(message_count, 0u);
	broker.flush();
	EXPECT_EQ(message_count, 1u);
}

TEST(event_broker, expired_listener_token_removes_listener) {
	event_broker broker;
	uint32_t message_count(0);
	{
		auto token =
			broker.register_listener<test_event>([&message_count](auto& /*event*/) { ++message_count; });
	}
	broker.publish(test_event{1});
	EXPECT_EQ(message_count, 0u);
}

TEST(event_broker, listener_token_can_be_copied) {
	event_broker broker;
	uint32_t message_count(0);
	{
		auto first_token =
			broker.register_listener<test_event>([&message_count](auto& /*event*/) { ++message_count; });
		auto second_token(first_token);
	}
	broker.publish(test_event{1});
	EXPECT_EQ(message_count, 0u);
}

TEST(event_broker, listener_token_can_expire_after_system) {
	auto broker = std::make_unique<event_broker>();
	auto first_token = broker->register_listener<test_event>([](auto& /*event*/) {});
	broker.reset();
}

TEST(event_broker, invalidated_listener_token_stops_events) {
	event_broker broker;
	uint32_t message_count(0);
	auto token = broker.register_listener<test_event>([&message_count](auto& /*event*/) { ++message_count; });
	auto tokenCopy(token); // even if a copy exists, invalidating the listener token will stop all events
	broker.publish(test_event{1});
	EXPECT_EQ(message_count, 1u);
	token.invalidate();
	broker.publish(test_event{1});
	EXPECT_EQ(message_count, 1u);
}

TEST(event_broker, publish_to_single_target) {
	event_broker broker;
	test_listener listener;
	EXPECT_EQ(listener.m_msg_count, 0u);
	broker.publish(test_event{}, &test_listener::on_event, &listener);
	EXPECT_EQ(listener.m_msg_count, 1u);	
}
