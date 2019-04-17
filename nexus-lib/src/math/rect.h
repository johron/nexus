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

	constexpr rect(T left, T top, T width, T height)
		: m_left(left)
		, m_top(top)
		, m_width(width)
		, m_height(height) {
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
}  // namespace nexus

/*
////////////////////////////////////////////////////////////
template <typename T>
bool Rect<T>::intersects(const Rect<T>& rectangle) const
{
	Rect<T> intersection;
	return intersects(rectangle, intersection);
}


////////////////////////////////////////////////////////////
template <typename T>
bool Rect<T>::intersects(const Rect<T>& rectangle, Rect<T>& intersection) const
{
	// Rectangles with negative dimensions are allowed, so we must handle them correctly

	// Compute the min and max of the first rectangle on both axes
	T r1MinX = std::min(left, static_cast<T>(left + width));
	T r1MaxX = std::max(left, static_cast<T>(left + width));
	T r1MinY = std::min(top, static_cast<T>(top + height));
	T r1MaxY = std::max(top, static_cast<T>(top + height));

	// Compute the min and max of the second rectangle on both axes
	T r2MinX = std::min(rectangle.left, static_cast<T>(rectangle.left + rectangle.width));
	T r2MaxX = std::max(rectangle.left, static_cast<T>(rectangle.left + rectangle.width));
	T r2MinY = std::min(rectangle.top, static_cast<T>(rectangle.top + rectangle.height));
	T r2MaxY = std::max(rectangle.top, static_cast<T>(rectangle.top + rectangle.height));

	// Compute the intersection boundaries
	T interLeft   = std::max(r1MinX, r2MinX);
	T interTop    = std::max(r1MinY, r2MinY);
	T interRight  = std::min(r1MaxX, r2MaxX);
	T interBottom = std::min(r1MaxY, r2MaxY);

	// If the intersection is valid (positive non zero area), then there is an intersection
	if ((interLeft < interRight) && (interTop < interBottom))
	{
		intersection = Rect<T>(interLeft, interTop, interRight - interLeft, interBottom - interTop);
		return true;
	}
	else
	{
		intersection = Rect<T>(0, 0, 0, 0);
		return false;
	}
}


*/