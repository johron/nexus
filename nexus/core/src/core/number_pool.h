#pragma once
#include <cstdint>

namespace nexus::util {
namespace detail {
template <class numeric_t>
struct wrap_around_validator {
	static void validate(numeric_t& num) {
		if (num == std::numeric_limits<numeric_t>::max()) {
			throw std::runtime_error("number_pool counter has wrapped around");
		}
	}
};
}  // namespace detail

template <class numeric_t, class validator_t = detail::wrap_around_validator<numeric_t>>
struct number_pool {
	constexpr number_pool(numeric_t initial_value = min())
		: m_number(initial_value) {}

	number_pool(const number_pool& other) = delete;
	number_pool& operator=(const number_pool& other) = delete;

	numeric_t next() {
		validator_t::validate(m_number);
		return m_number++;
	}

	void reset() {
		m_number = min();
	}

	[[nodiscard]] static constexpr numeric_t min() {
		return std::numeric_limits<numeric_t>::min();
	}

	[[nodiscard]] static constexpr numeric_t max() {
		return std::numeric_limits<numeric_t>::max();
	}

private:
	numeric_t m_number;
};

using pool_u8 = number_pool<uint8_t>;
using pool_u16 = number_pool<uint16_t>;
using pool_u32 = number_pool<uint32_t>;
using pool_u64 = number_pool<uint64_t>;

}  // namespace nexus::util