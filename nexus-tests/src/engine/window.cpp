#include "../include/nexus/nexus.h"
#include "../src/mock/window.h"
#include "gtest/gtest.h"

#define MOCK_WINDOW_TESTS

#ifdef MOCK_WINDOW_TESTS
using window_t = nexus::mock::window;
#else
using window_t = nexus::window;
#endif

TEST(window, construct_default) {
	window_t window;
}
TEST(window, construct_with_params) {
	window_t window(800, 600, "test window");
}
TEST(window, is_open) {
	window_t window(800, 600, "test window");
	EXPECT_TRUE(window.is_open());
	window.close();
	EXPECT_FALSE(window.is_open());
}