#pragma once
#include <chrono>
#include <ratio>

namespace nexus {
struct duration {
	template <class time_t>
	constexpr duration(time_t&& duration) 
		: m_duration(duration) {}

	[[nodiscard]] float to_seconds() const {
		return static_cast<float>(m_duration.count()) / std::nano::den;
	}

	[[nodiscard]] std::chrono::milliseconds to_milliseconds() const {
		return std::chrono::duration_cast<std::chrono::milliseconds>(m_duration);
	}

	[[nodiscard]] std::chrono::microseconds to_microseconds() const {
		return std::chrono::duration_cast<std::chrono::microseconds>(m_duration);
	}

private:
	std::chrono::nanoseconds m_duration;
};

struct timer {
	timer()
		: m_begin(clock::now()) {}

	[[maybe_unused]] duration reset() {
		const auto begin = m_begin;
		const auto now = clock::now();
		m_begin = now;
		return {now - begin};
	}

	[[nodiscard]] duration get_elapsed_time() const {
		return {clock::now() - m_begin};
	}

private:
	using clock = std::chrono::high_resolution_clock;
	clock::time_point m_begin;
};

}  // namespace nexus