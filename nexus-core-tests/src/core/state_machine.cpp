#include "../src/core/state_machine.h"

#include "gtest/gtest.h"

using namespace nexus;
using namespace std::chrono_literals;
struct base_state {};
struct init_state : public base_state {};
struct sleep_state : public base_state {
	sleep_state(std::chrono::milliseconds /*duration*/) {}
};

template <class state_t>
struct set_state {};

using test_state_machine = nexus::state_machine<base_state>;

TEST(state_machine, register_state) {
	test_state_machine states;
	states.register_state<init_state>();
	states.register_state<sleep_state>(250ms);
}

TEST(state_machine, initial_state) {
	test_state_machine states;
	states.register_state<init_state>();
	states.register_transition<set_state<init_state>>();
}