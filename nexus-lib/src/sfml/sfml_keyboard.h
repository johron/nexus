#pragma once
#include "SFML/Window/Keyboard.hpp"

namespace nexus {
using key = sf::Keyboard::Key;

namespace keyboard {
inline bool is_down(nexus::key key) {
	return sf::Keyboard::isKeyPressed(key);
}
}  // namespace keyboard
}  // namespace nexus
