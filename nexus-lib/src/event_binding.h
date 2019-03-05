#pragma once

namespace nexus {
template <class key_t, class event_t>
struct event_binding {
	template <class... functor_t>
	void bind(const key_t& key, functor_t&&... functor) {
		m_events[key] = [this, functor...]() { 
			invoke(functor...);
		};
	}

	template <class... functor_t>
	void append(const key_t& key, functor_t&&... functor) {
		if (!has_binding(key)) {
			bind(key, std::forward<functor_t>(functor)...);
		} else {
			bind(key, std::move(m_events[key]), std::forward<functor_t>(functor)...);
		}
	}

	[[nodiscard]] bool has_binding(const key_t key) const {
		return m_events.find(key) != m_events.end();
	}

	void trigger(const key_t& key) {
		auto iterator = m_events.find(key);
		if (iterator != m_events.end()) {
			(*iterator).second();
		}
	}

	void erase(const key_t& key) {
		m_events.erase(key);
	}

	[[nodiscard]] std::size_t size() const {
		return m_events.size();
	}

private:
	template <class functor_t>
	void invoke(functor_t&& last) {
		last();
	}

	template <class first_t, class... functor_t>
	void invoke(first_t&& head, functor_t&&... tail) {
		head();
		invoke(std::forward<functor_t>(tail)...);
	}

	std::map<key_t, event_t> m_events;
};
}  // namespace nexus