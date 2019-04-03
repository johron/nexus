#include "../src/events/event_dispatcher.h"
#include "../include/nexus/nexus.h"

#include "gtest/gtest.h"

using namespace nexus;

struct test_event {};

struct test_listener : public nexus::event_listener<test_event> {
	virtual void on_event(const test_event& /*event*/) override {
		++m_event_count;
	}

	int m_event_count = 0;
};

TEST(event_dispatcher, register_listener) {
	event_dispatcher dispatcher;
	auto listener = std::make_shared<test_listener>();

	dispatcher.register_listener<test_event>(listener);
	EXPECT_EQ(listener->m_event_count, 0);
	dispatcher.dispatch(test_event{});
	EXPECT_EQ(listener->m_event_count, 1);
}