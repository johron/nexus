#pragma once

namespace nexus {
template <class key_t, class event_t>
struct event_binding {
	using key = key_t;
	template <class... functor_t>
	void bind(const key_t& key, functor_t&&... functor) {
		m_events[key] = [this, functor...](auto&&... args) {
			[[maybe_unused]] int unused[] = {0, (functor(std::forward<decltype(args)>(args)...), 0)...};
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

	template <class... arg_t>
	void trigger(const key_t& key, arg_t&&... args) {
		auto iterator = m_events.find(key);
		if (iterator != m_events.end()) {
			(*iterator).second(std::forward<arg_t>(args)...);
		}
	}

	void erase(const key_t& key) {
		m_events.erase(key);
	}

	[[nodiscard]] std::size_t size() const {
		return m_events.size();
	}

private:
	std::map<key_t, event_t> m_events;
};
}  // namespace nexus