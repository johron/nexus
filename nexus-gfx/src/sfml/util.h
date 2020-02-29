#pragma once
#include "../gfx/color.h"

namespace nexus::util {
// utility interface to convert between engine and sfml types
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

inline auto make_color(const sf::Color& other) {
	return nexus::gfx::color{other.r, other.g, other.b, other.a};
}

inline auto make_color(const nexus::gfx::color& other) {
	return sf::Color(other.to_int());
}

}  // namespace nexus::sfml::util
