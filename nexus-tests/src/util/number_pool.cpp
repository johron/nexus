#include "gtest/gtest.h"
#include "../include/nexus/nexus.h"

using namespace nexus::util;

TEST(number_pool, next_sequence) {
	pool_u32 pool;
	for (uint32_t i = 0; i < 50; ++i) {
		EXPECT_EQ(pool.next(), i);
	}
}

TEST(number_pool, min) {
	constexpr pool_u32 pool;
	static_assert(pool.min() == std::numeric_limits<uint32_t>::min());
}

TEST(number_pool, max) {
	constexpr pool_u32 pool;
	static_assert(pool.max() == std::numeric_limits<uint32_t>::max());
}

TEST(number_pool, reset) {
	pool_u32 pool;
	for (uint32_t i = 0; i < 10; ++i) {
		EXPECT_EQ(pool.next(), i);
	}
	pool.reset();
	for (uint32_t i = 0; i < 10; ++i) {
		EXPECT_EQ(pool.next(), i);
	}
}

TEST(number_pool, wrap_around_causes_assert) {
	pool_u8 pool(255);
	try {
		const auto number = pool.next();
	} catch (const std::runtime_error& error){
		EXPECT_EQ(error.what(), std::string("number_pool counter has wrapped around"));
	}
}