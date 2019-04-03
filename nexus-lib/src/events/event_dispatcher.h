#pragma once
#include "event_listener.h"
#include <any>
#include <memory>

namespace nexus {

template <class event_t>
struct event_listener {
	virtual void on_event(const event_t& event) = 0;
};

struct event_dispatcher {
	template <class event_t>
	void register_listener(std::shared_ptr<event_listener<event_t>> listener) {
		const auto event_id = util::type_id::template get<event_t>();
		auto ptr = std::weak_ptr<event_listener<event_t>>(listener);
		m_listeners[event_id].emplace_back(ptr);
	}

	template <class event_t>
	void dispatch(event_t&& event) {
		const auto event_id = util::type_id::template get<event_t>();
		const auto& listeners = m_listeners[event_id];
		for (const auto& entry : listeners) {
			auto potential_listener = std::any_cast<std::weak_ptr<event_listener<event_t>>>(entry);
			if (auto active_listener = potential_listener.lock()) {
				active_listener->on_event(event);
			}
		}
	}

private:
	std::map<uint32_t, std::vector<std::any>> m_listeners;
};
}