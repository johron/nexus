#pragma once

namespace nexus {
template <class key_t, class keyboard_t>
struct concrete_keyboard {
	using key = key_t;
	static bool is_key_down(const key_t& key) {
		return keyboard_t::is_key_down(key);
	}
};
}  // namespace nexus