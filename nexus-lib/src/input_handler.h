#pragma once
#include <functional>

namespace nexus {
template <class key_t>
struct input_handler {
	template <class functor_t>
	void bind(const key_t& key, const functor_t& functor) {
		m_bindings[key] = functor;
	}

	bool has_binding(const key_t& key) const {
		return m_bindings.find(key) != m_bindings.end();
	}

	void clear(const key_t& key) {
		m_bindings.erase(key);
	}

	void trigger(const key_t& key) {
		const auto iterator = m_bindings.find(key);
		if (iterator != m_bindings.end()) {
			iterator->second();
		}
	}

private:
	std::map<key_t, std::function<void()>> m_bindings;
};
}  // namespace nexus