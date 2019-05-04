#include "gtest/gtest.h"
#include "../src/color.h"

TEST(color, to_integer) {
	nexus::color red(255, 0, 0, 255);
	EXPECT_EQ(red.to_int(), 0xff0000ff);
}