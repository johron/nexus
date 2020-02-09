#pragma once
#include "event_binding.h"

namespace nexus {
template <class key_t>
struct keyboard : public event_binding<key_t, std::function<void()>> {
	using key = key_t;

	static bool is_key_down(const key_t& key_code) {
		return keyboard_t::is_key_down(key_code);
	}
};

template <class button_t, class mouse_t>
struct concrete_mouse : public event_binding<button_t, std::function<void(const vector2i& position)>> {
	using button = button_t;

	static bool is_button_down(const button_t& btn_code) {
		return mouse_t::is_button_down(btn_code);
	}
};

}  // namespace nexus