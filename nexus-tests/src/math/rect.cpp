#include "gtest/gtest.h"
#include "../src/math/rect.h"

TEST(rect, default_constructor) {
	constexpr nexus::rect<int> empty_values;
	static_assert(empty_values.m_left == 0);
	static_assert(empty_values.m_top == 0);
	static_assert(empty_values.m_width == 0);
	static_assert(empty_values.m_height == 0);
}

TEST(rect, value_constructor) {
	constexpr nexus::rect<int> init_values{0, 1, 2, 3};
	static_assert(init_values.m_left == 0);
	static_assert(init_values.m_top == 1);
	static_assert(init_values.m_width == 2);
	static_assert(init_values.m_height == 3);
}

TEST(rect, comparison_operator) {
	constexpr nexus::rect<int> a(0, 0, 1, 1);
	constexpr nexus::rect<int> b(0, 0, 1, 1);
	static_assert(a == b);
	constexpr nexus::rect<int> c(1, 1, 0, 0);
	static_assert(a != c);
}

TEST(rect, contains_point) {
	constexpr nexus::rect<int> a(0, 0, 10, 10);
	static_assert(a.contains(2, 2));
	static_assert(!a.contains(nexus::vector2i(12, 2)));
}

TEST(rect, intersect_rect) {
	constexpr nexus::rect<int> a(0, 0, 5, 5);
	constexpr nexus::rect<int> b(3, 3, 5, 5);
	static_assert(a.intersects(b));
	constexpr nexus::rect<int> c(6, 6, 5, 5);
	static_assert(!a.intersects(c));
}