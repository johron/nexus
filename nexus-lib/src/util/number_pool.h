#pragma once

namespace nexus::util {
template <class numeric_t>
struct number_pool {
	constexpr number_pool(numeric_t initial_value = 0)
		: m_number(initial_value) {
	}

	numeric_t next() {
		assert(m_number < max() && "number_pool counter has wrapped around");
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