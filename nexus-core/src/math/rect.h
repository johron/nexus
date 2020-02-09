#pragma once
#include "vector.h"

namespace nexus {
template <class T>
struct rect {
	constexpr rect()
		: m_left(0)
		, m_top(0)
		, m_width(0)
		, m_height(0) {
	}

	template <class U>
	constexpr rect(U left, U top, U width, U height)
		: m_left(static_cast<T>(left))
		, m_top(static_cast<T>(top))
		, m_width(static_cast<T>(width))
		, m_height(static_cast<T>(height)) {
	}

	[[nodiscard]] constexpr bool operator==(const rect& other) const {
		return m_left == other.m_left && m_top == other.m_top && m_width == other.m_width &&
			   m_height == other.m_height;
	}

	[[nodiscard]] constexpr bool operator!=(const rect& other) const {
		return !(*this == other);
	}

	[[nodiscard]] constexpr bool contains(T x, T y) const {
		const T min_x = std::min(m_left, m_left + m_width);
		const T max_x = std::max(m_left, m_left + m_width);
		const T min_y = std::min(m_top, m_top + m_height);
		const T max_y = std::max(m_top, m_top + m_height);

		return (x >= min_x) && (x < max_x) && (y >= min_y) && (y < max_y);
	}

	[[nodiscard]] constexpr bool contains(const vector<T, 2>& point) const {
		return contains(point[0], point[1]);
	}

	[[nodiscard]] constexpr bool intersects(const rect& other) const {
		rect unused;
		return intersects(other, unused);
	}

	[[nodiscard]] constexpr bool intersects(const rect& other, rect& intersection) const {
		const T a_min_x = std::min(m_left, m_left + m_width);
		const T a_max_x = std::max(m_left, m_left + m_width);
		const T a_min_y = std::min(m_top, m_top + m_height);
		const T a_max_y = std::max(m_top, m_top + m_height);

		const T b_min_x = std::min(other.m_left, other.m_left + other.m_width);
		const T b_max_x = std::max(other.m_left, other.m_left + other.m_width);
		const T b_min_y = std::min(other.m_top, other.m_top + other.m_height);
		const T b_max_y = std::max(other.m_top, other.m_top + other.m_height);

		const T intersect_left = std::max(a_min_x, b_min_x);
		const T intersect_top = std::max(a_min_y, b_min_y);
		const T intersect_right = std::min(a_max_x, b_max_x);
		const T intersect_bottom = std::min(a_max_y, b_max_y);

		if ((intersect_left < intersect_right) && (intersect_top < intersect_bottom)) {
			intersection = rect{intersect_left,
								intersect_top,
								intersect_right - intersect_left,
								intersect_bottom - intersect_top};
			return true;
		} else {
			intersection = rect{};
			return false;
		}
	}

	T m_left;
	T m_top;
	T m_width;
	T m_height;
};

using rectf = rect<float>;
using recti = rect<int>;

}  // namespace nexus

