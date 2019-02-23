#include "../src/math/vector.h"
#include "gtest/gtest.h"

using namespace nexus::math;

TEST(vector, constructor_default) {
	constexpr vector2i vector2;
	constexpr vector3f vector3;
}

TEST(vector, constructor_values) {
	constexpr vector2i a(1, 2);
	constexpr vector2i b(1.234f, 6.789f);
}

TEST(vector, constructor_copy) {
	// constexpr vector2f first(1, 2);
	// constexpr vector2i second(first);
	// constexpr vector2i second(vector2f(1.f, 2.f));
// 
// 	constexpr auto a = detail::vector_base<int, 2>(1, 2);
// 	constexpr auto b = detail::vector_base<int, 2>(a);
// 	constexpr auto c = detail::vector_base<float, 2>(a);

	constexpr auto v1 = vector2i(1, 2);
	constexpr auto v2 = vector2f(v1);

	// static_assert(first == second, "Copy constructor did not result in identical data");
}