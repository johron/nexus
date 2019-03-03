#include <type_traits>
#include "../include/nexus/nexus.h"
#include "gtest/gtest.h"

TEST(vector, construct_default) {
	constexpr nexus::vector2i vec2;
	constexpr nexus::vector3i vec3;
}

TEST(vector, construct_from_args) {
	constexpr nexus::vector2i vec{1, 2};
	EXPECT_EQ(vec.x, 1);
	EXPECT_EQ(vec.y, 2);
}

TEST(vector, construct_from_copy) {
	const nexus::vector2i vec_1{1, 2};
	const nexus::vector2f vec_2(vec_1);
	EXPECT_EQ(vec_1, vec_2);
}

TEST(vector, size) {
	constexpr nexus::vector2i vec2{1, 2};
	static_assert(vec2.size() == 2, "incorrect vector size");

	constexpr nexus::vector3i vec3{1, 2, 3};
	static_assert(vec3.size() == 3, "incorrect vector size");
}

TEST(vector, iterator_access) {
	constexpr nexus::vector2i vec{1, 2};
	int expected_value = 1;
	for (const auto& element : vec) {
		EXPECT_EQ(expected_value, element);
		expected_value++;
	}
}

TEST(vector, subscript_operator) {
	constexpr nexus::vector2i vec{1, 2};
	static_assert(vec[0] == 1, "subscript operator failed");
	static_assert(vec[1] == 2, "subscript operator failed");
}

TEST(vector, comparison_operator) {
	constexpr nexus::vector2i vec_1{1, 2};
	constexpr nexus::vector2i vec_2{2, 3};
	static_assert(vec_1 != vec_2, "vector comparison failed");
	static_assert(vec_1 == nexus::vector2i(1, 2), "vector comparison failed");
}

TEST(vector, comparison_different_types) {
	constexpr nexus::vector2i vec_1{1.f, 2.f};
	constexpr nexus::vector2f vec_2{1, 2};
	static_assert(vec_1 == vec_2, "vector comparison with different typed failed");
}

TEST(vector, addition) {
	constexpr nexus::vector2i vec_1{1, 2};
	constexpr nexus::vector2i vec_2{3, 4};
	constexpr auto result = vec_1 + vec_2;
	EXPECT_EQ(result.x, vec_1.x + vec_2.x);
	EXPECT_EQ(result.y, vec_1.y + vec_2.y);
}

TEST(vector, addition_composite) {
	nexus::vector2i vec_1{1, 2};
	vec_1 += nexus::vector2i{2, 3};
	EXPECT_EQ(vec_1, nexus::vector2i(3, 5));
}

TEST(vector, subtraction) {
	constexpr nexus::vector2i vec_1{1, 2};
	constexpr nexus::vector2i vec_2{3, 4};
	constexpr auto result = vec_1 - vec_2;
	EXPECT_EQ(result.x, vec_1.x - vec_2.x);
	EXPECT_EQ(result.y, vec_1.y - vec_2.y);
}

TEST(vector, subtraction_composite) {
	nexus::vector2i vec_1{1, 2};
	vec_1 -= nexus::vector2i{2, 3};
	EXPECT_EQ(vec_1, nexus::vector2i(-1, -1));
}

TEST(vector, scalar_multiplication) {
	constexpr nexus::vector2i vec_1{1, 2};
	constexpr auto result = vec_1 * 2.5f;
	// scalar multiplication CAN change the returned storage type for the vector
	static_assert(std::is_same_v<decltype(result), const nexus::vector2f>, "multiplication return value");
	EXPECT_EQ(result.x, 2.5f);
	EXPECT_EQ(result.y, 5.0f);
}

TEST(vector, composite_scalar_multiplication) {
	nexus::vector2i vec{1, 2};
	vec *= 2.5f;
	// compound scalar multiplication CAN NOT change the storage type for the vector
	static_assert(std::is_same_v<decltype(vec), nexus::vector2i>, "multiplication return value");
	EXPECT_EQ(vec.x, 2);
	EXPECT_EQ(vec.y, 5);
}

TEST(vector, scalar_division) {
	constexpr nexus::vector2i vec{2, 5};
	constexpr auto result = vec / 2.f;
	// scalar division CAN change the returned storage type for the vector
	static_assert(std::is_same_v<decltype(result), const nexus::vector2f>, "division return value");
	EXPECT_EQ(result.x, 1);
	EXPECT_EQ(result.y, 2.5f);
}

TEST(vector, composite_scalar_division) {
	nexus::vector2i vec{2, 5};
	vec /= 2;
	// compound scalar division CAN NOT change the storage type for the vector
	static_assert(std::is_same_v<decltype(vec), nexus::vector2i>, "division return value");
	EXPECT_EQ(vec.x, 1);
	EXPECT_EQ(vec.y, 2);
}