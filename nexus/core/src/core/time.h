#pragma once
#include <chrono>
#include <ratio>

namespace nexus {
struct duration : public std::chrono::nanoseconds {
	template <class time_t>
	duration(time_t&& duration) 
		: std::chrono::nanoseconds(duration) {}

	[[nodiscard]] float to_seconds() const {
		return static_cast<float>(count()) / std::nano::den;
	}

	[[nodiscard]] std::chrono::milliseconds to_milliseconds() const {
		return std::chrono::duration_cast<std::chrono::milliseconds>(*this);
	}

	[[nodiscard]] std::chrono::microseconds to_microseconds() const {
		return std::chrono::duration_cast<std::chrono::microseconds>(*this);
	}
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