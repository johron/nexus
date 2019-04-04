#include "../src/events/event_broadcaster.h"
#include "../include/nexus/nexus.h"

#include "gtest/gtest.h"

using namespace nexus;

struct test_event_1 {
	int m_number;
};

struct test_event_2 {
	std::string m_string;
};

struct test_listener : public nexus::event_listener<test_event_1>,
					   public nexus::event_listener<test_event_2> {
	
	virtual void on_event(const test_event_1& event) override {
		m_numbers.push_back(event.m_number);
	}

	virtual void on_event(const test_event_2& event) override {
		m_strings.push_back(event.m_string);
	}

	std::vector<int> m_numbers;
	std::vector<std::string> m_strings;
};

TEST(event_broadcaster, register_listener) {
	event_broadcaster broadcaster;
	auto listener = std::make_shared<test_listener>();
	broadcaster.register_listener<test_event_1>(listener);
	EXPECT_EQ(broadcaster.listener_count<test_event_1>(), 1u);
}

TEST(event_broadcaster, remove_listener) {
	event_broadcaster broadcaster;
	auto listener = std::make_shared<test_listener>();
	broadcaster.register_listener<test_event_1>(listener);
	EXPECT_EQ(broadcaster.listener_count<test_event_1>(), 1u);
	broadcaster.remove_listener<test_event_1>(listener);
	EXPECT_EQ(broadcaster.listener_count<test_event_1>(), 0u);
}

TEST(event_broadcaster, post_event) {
	event_broadcaster broadcaster;
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
	event_broadcaster broadcaster;
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