#pragma once
#include "../math/vector.h"

namespace nexus::sfml::util {
// utility interface to convert between engine vector and sfml vector
template <class T>
inline auto make_vector(const sf::Vector2<T>& other) {
	return nexus::vector<T, 2>{other.x, other.y};
}

template <class T>
inline auto make_vector(const nexus::vector<T, 2>& other) {
	return sf::Vector2<T>{other.x, other.y};
}
}