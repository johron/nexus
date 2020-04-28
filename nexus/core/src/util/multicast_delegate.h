#pragma once
#include <functional>
#include <optional>

namespace nexus {
namespace test {
template <class invalid_t>
struct one_shot_event {
	static_assert(!std::is_invocable_v<invalid_t>, "invalid function signature");
};

template <class return_t, class... arg_t>
struct one_shot_event<return_t(arg_t...)> {
	using function_t = std::function<return_t(arg_t...)>;
	one_shot_event() = default;
	one_shot_event(const one_shot_event& other) = delete;
	one_shot_event(function_t function)
		: m_function(std::make_unique<function_t>(function)) {}

	one_shot_event& operator=(const one_shot_event& other) = delete;

	template <class return_type = return_t, std::enable_if_t<std::is_same_v<return_type, void>>* = nullptr>
	void operator()(arg_t... args) {
		if (!m_function) {
			throw std::runtime_error("one_shot_event invoked multiple times");
		} 
		
		auto func = std::exchange(m_function, nullptr);
		(*func)(args...);
	}

	template <class return_type = return_t, std::enable_if_t<!std::is_same_v<return_type, void>>* = nullptr>
	return_type operator()(arg_t... args) {
		if (!m_function) {
			throw std::runtime_error("one_shot_event invoked multiple times");
		} 

		auto func = std::exchange(m_function, nullptr);
		return (*func)(args...);
	}

	[[nodiscard]] bool empty() const {
		return m_function.operator bool();
	}

	operator bool() const {
		return !empty();
	}

private:
	std::unique_ptr<function_t> m_function;
};

struct cancel_token {
	std::function<void()> test;

private:
	// one_shot_event<void()> m_cancel_function;
};

/*
struct cancel_token {
	cancel_token(std::function<void()> on_cancel) {}

	cancel_token(event_broker* system, std::type_index event_id, uint32_t listener_id)
		: m_system(system)
		, m_event_id(event_id)
		, m_listener_id(listener_id) {}

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
	std::function<void()> m_function;
};

struct listener_token {
	listener_token(std::shared_ptr<cancel_token> token)
		: m_token(token) {}

	listener_token(const listener_token& other) {
		*this = other;
	}

	listener_token(listener_token&& other) {
		*this = std::forward<listener_token>(other);
	}

	listener_token& operator=(const listener_token& other) {
		m_token = other.m_token;
		return *this;
	}

	listener_token& operator=(listener_token&& other) {
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
*/
}  // namespace test

template <class owner_t>
struct cancel_token {};

template <class... arg_t>
struct multicast_delegate {
	using function_t = std::function<void(arg_t...)>;
	using delegate_t = multicast_delegate<arg_t...>;

	void add(function_t function) {
		m_functions.push_back(function);
	}

	template <class object_t, class funcptr_t>
	void add(object_t* object, const funcptr_t& funcptr) {
		add([object, funcptr](arg_t... args) { (object->*funcptr)(args...); });
	}

	void clear() {
		m_functions.clear();
	}

	void broadcast(arg_t... args) {
		for (const auto& func : m_functions) {
			func(args...);
		}
	}

	std::size_t size() const {
		return m_functions.size();
	}

private:
	std::vector<function_t> m_functions;
};
}  // namespace nexus