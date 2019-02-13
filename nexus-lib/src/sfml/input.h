#pragma once
#include "SFML/Window/Keyboard.hpp"

namespace nexus {
using key = sf::Keyboard::Key;

struct input_binding {
	void bind(nexus::key key, std::function<void()> action) {
		m_bindings[key] = action;
	}

	void trigger(nexus::key key) {
		auto iterator = m_bindings.find(key);
		if (iterator != m_bindings.end()) {
			iterator->second();
		}
	}

private:
	std::map<nexus::key, std::function<void()>> m_bindings;
};
}  // namespace nexus