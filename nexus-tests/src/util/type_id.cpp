#include "gtest/gtest.h"
#include "../include/nexus/nexus.h"

using namespace nexus::util;

TEST(type_id, unique_id_for_standard_types) {
	EXPECT_NE(type_id::get<int>(), type_id::get<float>());
}

TEST(type_id, unique_id_for_custom_types) {
	struct custom_type {};
	EXPECT_EQ(type_id::get<custom_type>(), type_id::get<custom_type>());
}