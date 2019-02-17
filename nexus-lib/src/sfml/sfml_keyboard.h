#pragma once
#include "SFML/Window/Keyboard.hpp"

namespace nexus {
struct keyboard {
	enum class key {
		a = sf::Keyboard::Key::A,
		b = sf::Keyboard::Key::B,
		c = sf::Keyboard::Key::C,
		d = sf::Keyboard::Key::D,
		e = sf::Keyboard::Key::E,
		f = sf::Keyboard::Key::F,
		g = sf::Keyboard::Key::G,
		h = sf::Keyboard::Key::H,
		i = sf::Keyboard::Key::I,
		j = sf::Keyboard::Key::J,
		k = sf::Keyboard::Key::K,
		l = sf::Keyboard::Key::L,
		m = sf::Keyboard::Key::M,
		n = sf::Keyboard::Key::N,
		o = sf::Keyboard::Key::O,
		p = sf::Keyboard::Key::P,
		q = sf::Keyboard::Key::Q,
		r = sf::Keyboard::Key::R,
		s = sf::Keyboard::Key::S,
		t = sf::Keyboard::Key::T,
		u = sf::Keyboard::Key::U,
		v = sf::Keyboard::Key::V,
		w = sf::Keyboard::Key::W,
		x = sf::Keyboard::Key::X,
		y = sf::Keyboard::Key::Y,
		z = sf::Keyboard::Key::Z,
		num_0 = sf::Keyboard::Key::Num0,
		num_1 = sf::Keyboard::Key::Num1,
		num_2 = sf::Keyboard::Key::Num2,
		num_3 = sf::Keyboard::Key::Num3,
		num_4 = sf::Keyboard::Key::Num4,
		num_5 = sf::Keyboard::Key::Num5,
		num_6 = sf::Keyboard::Key::Num6,
		num_7 = sf::Keyboard::Key::Num7,
		num_8 = sf::Keyboard::Key::Num8,
		num_9 = sf::Keyboard::Key::Num9,
		escape = sf::Keyboard::Key::Escape,
		left_ctrl = sf::Keyboard::Key::LControl,
		left_shift = sf::Keyboard::Key::LShift,
		left_alt = sf::Keyboard::Key::LAlt,
		left_system = sf::Keyboard::Key::LSystem,
		right_ctrl = sf::Keyboard::Key::RControl,
		right_shift = sf::Keyboard::Key::RShift,
		right_alt = sf::Keyboard::Key::RAlt,
		right_system = sf::Keyboard::Key::RSystem,
		menu = sf::Keyboard::Key::Menu,
		left_bracket = sf::Keyboard::Key::LBracket,
		right_bracket = sf::Keyboard::Key::RBracket,
		semicolon = sf::Keyboard::Key::Semicolon,
		comma = sf::Keyboard::Key::Comma,
		period = sf::Keyboard::Key::Period,
		quote = sf::Keyboard::Key::Quote,
		slash = sf::Keyboard::Key::Slash,
		backslash = sf::Keyboard::Key::Backslash,
		tilde = sf::Keyboard::Key::Tilde,
		equal = sf::Keyboard::Key::Equal,
		hyphen = sf::Keyboard::Key::Hyphen,
		space = sf::Keyboard::Key::Space,
		enter = sf::Keyboard::Key::Enter,
		backspace = sf::Keyboard::Key::Backspace,
		tab = sf::Keyboard::Key::Tab,
		page_up = sf::Keyboard::Key::PageUp,
		page_down = sf::Keyboard::Key::PageDown,
		end = sf::Keyboard::Key::End,
		home = sf::Keyboard::Key::Home,
		insert = sf::Keyboard::Key::Insert,
		del = sf::Keyboard::Key::Delete,
		plus = sf::Keyboard::Key::Add,
		minus = sf::Keyboard::Key::Subtract,
		multiply = sf::Keyboard::Key::Multiply,
		divide = sf::Keyboard::Key::Divide,
		arrow_left = sf::Keyboard::Key::Left,
		arrow_right = sf::Keyboard::Key::Right,
		arrow_up = sf::Keyboard::Key::Up,
		arrow_down = sf::Keyboard::Key::Down,

	};
	inline bool is_down(key key) {
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key));
	}
};
}  // namespace nexus::sfml
