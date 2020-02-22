#pragma once
#include <typeindex>

namespace nexus {
template <class state_t>
struct state_machine {
	template <class state_t, class... arg_t>
	void register_state(arg_t... args) {
		m_states.insert(
			{std::type_index(typeid(state_t)), std::make_unique<state_t>(std::forward<arg_t>(args)...)});
	}

	template <class transition_t>
	void register_transition() {

	}

	std::map<std::type_index, std::unique_ptr<state_t>> m_states;
};
}