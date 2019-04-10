#pragma once
#include "../util/number_pool.h"
#include "../util/type_id.h"

namespace nexus {

struct event_system {
	struct cancel_token {
		cancel_token(event_system* system, uint32_t event_id, uint32_t listener_id)
			: m_system(system)
			, m_event_id(event_id)
			, m_listener_id(listener_id) {
		}

		~cancel_token() {
			detach();
		}

		void detach() {
			if (m_system) {
				m_system->remove_listener(m_event_id, m_listener_id);
				m_system = nullptr;
			}
		}

		[[nodiscard]] bool is_detached() const {
			return m_system == nullptr;
		}

	private:
		event_system* m_system;
		uint32_t m_event_id;
		uint32_t m_listener_id;
	};

	struct listener {
		listener() = default;
		~listener() = default;

		listener(std::shared_ptr<cancel_token> token)
			: m_token(token) {
		}

		listener(const listener& other) {
			*this = other;
		}

		listener(listener&& other) {
			*this = std::forward<listener>(other);
		}

		listener& operator=(const listener& other) {
			m_token = other.m_token;
			return *this;
		}

		listener& operator=(listener&& other) {
			std::swap(m_token, other.m_token);
			return *this;
		}

		void invalidate() {
			if (is_valid()) {
				m_token->detach();
			}
		}

		[[nodiscard]] bool is_valid() const {
			return m_token && !m_token->is_detached();
		}

	private:
		std::shared_ptr<cancel_token> m_token;
	};

	event_system() = default;
	~event_system() {
		detach_all();
	}

	event_system(const event_system& other) = delete;
	event_system(event_system&& other) = delete;
	event_system& operator=(const event_system& other) = delete;
	event_system& operator=(event_system&& other) = delete;

	template <class event_t>
	[[nodiscard]] listener register_listener(std::function<void(const event_t& event)> func) {
		const auto event_id = util::type_id::template get<event_t>();
		const auto listener_id = m_listener_id_pool.next();
		const auto token = std::make_shared<cancel_token>(this, event_id, listener_id);
		m_listeners[event_id][listener_id] = listener_data{func, token};
		return listener{token};
	}

	void remove_listener(uint32_t event_id, uint32_t listener_id) {
		auto& listeners = m_listeners[event_id];
		listeners.erase(listener_id);
	}

	template <class event_t>
	void post(const event_t& event) {
		const auto event_id = util::type_id::template get<event_t>();
		auto& listeners = m_listeners[event_id];
		using callback = std::function<void(const event_t&)>;
		for (auto& entry : listeners) {
			const auto& func = std::any_cast<callback>(entry.second.m_function);
			func(event);
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
	void detach_all() {
		listener_tree empty;
		std::swap(m_listeners, empty);
		for (auto& group : empty) {
			for (auto& entry : group.second) {
				if (auto current_data = entry.second.m_token.lock()) {
					current_data->detach();
				} else {
					throw std::runtime_error(
						"found dead listener that should already have been removed - investigate!");
				}
			}
		}
	}

	struct listener_data {
		std::any m_function;
		std::weak_ptr<cancel_token> m_token;
	};

	using listener_id_t = uint32_t;
	using message_id_t = uint32_t;
	using listener_group = std::map<listener_id_t, listener_data>;
	using listener_tree = std::map<message_id_t, listener_group>;
	listener_tree m_listeners;
	std::vector<std::function<void()>> m_message_queue;
	util::pool_u32 m_listener_id_pool;
};
}  // namespace nexus