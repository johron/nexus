#include "../include/nexus/nexus.h"
#include "gtest/gtest.h"

using cache_t = nexus::resource_cache<std::string, int>;

TEST(resource_cache, construct_default) {
	[[maybe_unused]] cache_t cache;
}

TEST(resource_cache, load) {
	cache_t cache;
	//cache.load(11);
}
