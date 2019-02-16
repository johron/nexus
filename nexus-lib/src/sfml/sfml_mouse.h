#pragma once
#include "SFML/Window/Mouse.hpp"

namespace nexus::mouse {
enum class button {
	left = sf::Mouse::Button::Left,
	right = sf::Mouse::Button::Right,
	middle = sf::Mouse::Button::Middle,
	extra_1 = sf::Mouse::Button::XButton1,
	extra_2 = sf::Mouse::Button::XButton2
};

inline bool is_down(button button) {
	return sf::Mouse::isButtonPressed(sf::Mouse::Button(button));
}
}  // namespace nexus::mouse