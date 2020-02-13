#pragma once
#include "../math/rect.h"
#include "../math/vector.h"

namespace nexus::util {
// utility interface to convert between engine vector and sfml vector
template <class T>
inline auto make_vector(const sf::Vector2<T>& other) {
	return nexus::vector<T, 2>{other.x, other.y};
}

template <class T>
inline auto make_vector(const nexus::vector<T, 2>& other) {
	return sf::Vector2<T>{other.x, other.y};
}
template <class T>
inline auto make_rect(const nexus::rect<T>& other) {
	return sf::Rect<T>(other.m_left, other.m_top, other.m_width, other.m_height);
}

template <class T>
inline auto make_rect(const sf::Rect<T>& other) {
	return nexus::rect<T>(other.left, other.top, other.width, other.height);
}
}  // namespace nexus::sfml::util
