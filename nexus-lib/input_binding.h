#pragma once
#include "key_code.h"

namespace nexus {
struct input_binding {
	void bind(nexus::key key, std::function<void()> action) {
		m_bindings[key] = action;
	}

	bool has_binding(nexus::key key) const {
		return m_bindings.find(key) != m_bindings.end();
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