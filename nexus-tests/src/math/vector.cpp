#include "gtest/gtest.h"
#include "../src/math/vector.h"

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
	//constexpr vector2f first(1, 2);
	//constexpr vector2i second(vector2f(1,2));
	//static_assert(first == second, "Copy constructor did not result in identical data");
}