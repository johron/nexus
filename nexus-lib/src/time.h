#pragma once
#include <chrono>

namespace nexus {
struct time {
	template <class duration_t>
	time(const duration_t& duration)
		: m_duration(duration) {
	}

	time(const time& other) = default;
	time(time&& other) = default;
	time& operator=(const time& other) = default;
	time& operator=(time&& other) = default;

	[[nodiscard]] auto as_minutes() const {
		return std::chrono::duration_cast<std::chrono::minutes>(m_duration).count();
	}

	[[nodiscard]] auto as_milliseconds() const {
		return std::chrono::duration_cast<std::chrono::milliseconds>(m_duration).count();
	}

	[[nodiscard]] auto as_microseconds() const {
		return std::chrono::duration_cast<std::chrono::microseconds>(m_duration).count();
	}

	[[nodiscard]] float as_seconds() const {
		return as_milliseconds() / 1000.0f;
	}

	[[nodiscard]] auto as_duration() const {
		return m_duration;
	}

private:
	std::chrono::steady_clock::duration m_duration;
};

struct timer {
	timer()
		: m_begin(std::chrono::steady_clock::now()) {
	}

	[[nodiscard]] time elapsed_time() const {
		return time{(std::chrono::steady_clock::now() - m_begin)};
	}

	[[nodiscard]] time reset() {
		auto now = std::chrono::steady_clock::now();
		std::swap(now, m_begin);
		return time{m_begin - now};
	}

private:
	std::chrono::steady_clock::time_point m_begin;
};
}  // namespace nexus