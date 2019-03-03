#include "../include/nexus/nexus.h"
#include "gtest/gtest.h"
#ifdef TEST_WINDOW_IMPLEMENTATION
TEST(window, construct_default) {
	nexus::window window;
}

TEST(window, construct_with_params) {
	nexus::window window(800, 600, "test window");
}

TEST(window, is_open) {
	nexus::window window(800, 600, "test window");
	EXPECT_TRUE(window.is_open());
	window.close();
	EXPECT_FALSE(window.is_open());
}

#endif