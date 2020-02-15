#pragma once

namespace nexus::keyboard {
// clang-format off
enum class key {
	unknown = -1,
	a = 0, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
	
	num_0, num_1, num_2, num_3, num_4, 
	num_5, num_6, num_7, num_8, num_9,

	escape,
	l_control, l_shift, l_alt, l_system,
	r_control, r_shift, r_alt, r_system,
	menu,
	l_bracket,
	r_bracket,
	semicolon,
	comma,
	period,
	quote,
	slash,
	backslash,
	tilde,
	equal,
	hyphen,
	space,
	enter,
	backspace,
	tab,
	pageup,
	pagedown,
	end,
	home,
	insert,
	del,
	add,
	subtract,
	multiply,
	divide,
	arrow_left,
	arrow_right,
	arrow_up,
	arrow_down,
	numpad_0, numpad_1, numpad_2, numpad_3, numpad_4,
	numpad_5, numpad_6, numpad_7, numpad_8, numpad_9,
	f1, f2, f3, f4, f5, f6, f7, f8, 
	f9, f10, f11, f12, f13, f14, f15,
	pause,
};
// clang-format on

static bool is_key_down(const key& key) {
	return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
}
}	// namespace nexus::keyboard
