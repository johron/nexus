#pragma once
#include "../utils/type_id.h"
#include "event_listener.h"

namespace nexus {
template <class event_t>
struct event_listener {
	virtual ~event_listener() = default;
	virtual void on_event(const event_t& event) = 0;
};

struct event_broadcaster {
	template <class event_t>
	void register_listener(std::shared_ptr<event_listener<event_t>> listener) {
		const auto event_id = util::type_id::template get<event_t>();
		using listener_t = std::weak_ptr<event_listener<event_t>>;
		m_listeners[event_id].emplace_back(listener_t(listener));
	}

	template <class event_t>
	void remove_listener(std::shared_ptr<event_listener<event_t>> listener) {
		const auto event_id = util::type_id::template get<event_t>();
		auto& listeners = m_listeners[event_id];
		using listener_t = std::weak_ptr<event_listener<event_t>>;

		for (int i = listeners.size() - 1; i >= 0; --i) {
			const auto potential_listener = std::any_cast<listener_t>(listeners[i]);
			if (auto active_listener = potential_listener.lock()) {
				if (active_listener == listener) {
					listeners.erase(listeners.begin() + i);
				}
			}
		}
	}

	template <class event_t>
	void post(const event_t& event) {
		const auto event_id = util::type_id::template get<event_t>();
		auto& listeners = m_listeners[event_id];

		using listener_t = std::weak_ptr<event_listener<event_t>>;
		for (int i = listeners.size() - 1; i >= 0; --i) {
			const auto potential_listener = std::any_cast<listener_t>(listeners[i]);
			if (auto active_listener = potential_listener.lock()) {
				active_listener->on_event(event);
			} else {
				listeners.erase(listeners.begin() + i);
			}
		}
	}

	template <class event_t>
	void enqueue(event_t&& event) {
		m_message_queue.emplace_back([event, this]() { post(event); });
	}

	void flush() {
		std::vector<std::function<void()>> empty_queue;
		std::swap(empty_queue, m_message_queue);
		for (const auto& message : empty_queue) {
			message();
		}
	}

	template <class event_t>
	[[nodiscard]] std::size_t listener_count() const {
		const auto event_id = util::type_id::template get<event_t>();
		const auto it = m_listeners.find(event_id);
		return it != m_listeners.end() ? it->second.size() : 0;
	}

private:
	std::map<uint32_t, std::vector<std::any>> m_listeners;
	std::vector<std::function<void()>> m_message_queue;
};
}  // namespace nexus