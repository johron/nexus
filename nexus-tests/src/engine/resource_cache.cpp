#include "../include/nexus/nexus.h"
#include "gtest/gtest.h"

enum class enumerated_id { id_1, id_2, id_3, invalid };

// resources which can be constructed by only accepting the key
// as arguments for the constructor do not need a custom loader defined.
struct default_resource {
	default_resource(enumerated_id id)
		: m_id(id) {
	}

	enumerated_id m_id;
};

// resources that need more/other data for construction will need a custom
// loader implemented that can convert the key to the expected arguments.
struct custom_resource {
	custom_resource(int id, std::string text)
		: m_id(id)
		, m_text(text) {
	}

	int m_id;
	std::string m_text;
};

template <>
struct nexus::loader<custom_resource> {
	static std::shared_ptr<custom_resource> get(enumerated_id id) {
		switch (id) {
			case enumerated_id::id_1:
				return std::make_shared<custom_resource>(1, "resource one");
			case enumerated_id::id_2:
				return std::make_shared<custom_resource>(2, "resource two");
			case enumerated_id::id_3:
				return std::make_shared<custom_resource>(3, "resource three");
			default:
				return nullptr;
		}
	}
};

using custom_cache = nexus::resource_cache<enumerated_id, custom_resource>;
using default_cache = nexus::resource_cache<enumerated_id, default_resource>;

TEST(resource_cache, construct_default) {
	[[maybe_unused]] custom_cache cache;
}

TEST(resource_cache, is_loaded) {
	default_cache cache;
	EXPECT_FALSE(cache.is_loaded(enumerated_id::id_1));
	EXPECT_FALSE(cache.is_loaded(enumerated_id::id_2));
	EXPECT_FALSE(cache.is_loaded(enumerated_id::id_3));
}

TEST(resource_cache, load_success) {
	custom_cache first;
	EXPECT_FALSE(first.is_loaded(enumerated_id::id_1));
	first.load(enumerated_id::id_1); // using custom loader
	EXPECT_TRUE(first.is_loaded(enumerated_id::id_1));

	default_cache second;
	EXPECT_FALSE(second.is_loaded(enumerated_id::id_1));
	second.load(enumerated_id::id_1); // using default loader
	EXPECT_TRUE(second.is_loaded(enumerated_id::id_1));
}

TEST(resource_cache, load_failed) {
	custom_cache cache;
	EXPECT_FALSE(cache.is_loaded(enumerated_id::invalid));
	try {
		cache.load(enumerated_id::invalid);
	} catch(const std::exception& exception) {
		EXPECT_EQ(exception.what(), std::string("failed to load resource"));
	}
}

TEST(resource_cache, size) {
	default_cache cache;
	EXPECT_EQ(cache.size(), 0u);
	cache.load(enumerated_id::id_1);
	cache.load(enumerated_id::id_1);
	EXPECT_EQ(cache.size(), 1u);
	cache.load(enumerated_id::id_2);
	EXPECT_EQ(cache.size(), 2u);
}

TEST(resource_cache, get_triggers_load) {
	default_cache cache;
	auto resource = cache.get(enumerated_id::id_1);
	EXPECT_EQ(cache.size(), 1u);
	EXPECT_NE(resource, nullptr);
}

TEST(resource_cache, release_unused) {
	default_cache cache;
	auto resource_1 = cache.get(enumerated_id::id_1);
	auto resource_2 = cache.get(enumerated_id::id_2);
	EXPECT_EQ(cache.size(), 2u);
	cache.release_unused();
	EXPECT_EQ(cache.size(), 2u);
	resource_1.reset();
	cache.release_unused();
	EXPECT_EQ(cache.size(), 1u);
}