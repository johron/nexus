#include "../src/core/module_manager.h"
#include "gtest/gtest.h"

using namespace nexus;
static constexpr auto the_update_time = std::chrono::milliseconds(10);

struct test_module {};
struct test_module_1 : public test_module {};
struct test_module_2 : public test_module {};
struct test_module_3 : public test_module {};

using test_module_manager = module_manager<test_module>;

TEST(module_manager, register_module) {
	test_module_manager manager;
	EXPECT_FALSE(manager.is_loaded<test_module_1>());
	EXPECT_FALSE(manager.is_registered<test_module_1>());
	manager.register_module<test_module_1>();
	EXPECT_FALSE(manager.is_loaded<test_module_1>());
	EXPECT_TRUE(manager.is_registered<test_module_1>());
}

TEST(module_manager, insert_module) {
	test_module_manager manager;
	EXPECT_FALSE(manager.is_loaded<test_module_1>());
	EXPECT_FALSE(manager.is_registered<test_module_1>());
	manager.insert_module<test_module_1>();
	EXPECT_TRUE(manager.is_loaded<test_module_1>());
	EXPECT_TRUE(manager.is_registered<test_module_1>());
}

struct numeric_module : public test_module {
	explicit numeric_module(int number)
		: m_number(number) {}
	int m_number;
};

struct fixed_ten_module : public numeric_module {
	fixed_ten_module()
		: numeric_module(10) {}
};

TEST(module_manager, module_alias) {
	test_module_manager manager;
	manager.insert_module<fixed_ten_module, numeric_module>();
	auto& sample = manager.get<numeric_module>();
	EXPECT_EQ(sample.m_number, 10);
}

TEST(module_manager, get_module) {
	test_module_manager manager;
	manager.register_module<test_module_1>();
	manager.load<test_module_1>();
	const auto& sample_module = manager.get<test_module_1>();
	static_assert(std::is_same_v<std::decay_t<decltype(sample_module)>, test_module_1>);
}

TEST(module_manager, visit_sequential) {
	test_module_manager manager;
	manager.register_module<test_module_1>();
	manager.register_module<test_module_2>();
	manager.visit([](test_module&) {}, std::execution::seq);
}

TEST(module_manager, visit_parallel) {
	test_module_manager manager;
	manager.register_module<test_module_1>();
	manager.register_module<test_module_2>();

	struct update_visitor {
		void operator()(test_module&) {}
	};
	manager.visit(update_visitor{}, std::execution::par);
}

TEST(module_manager, load_single) {
	test_module_manager manager;
	manager.register_module<test_module_1>();
	manager.register_module<test_module_2>();
	manager.register_module<test_module_3>();
	manager.load<test_module_1>();
	EXPECT_TRUE(manager.is_loaded<test_module_1>());
	EXPECT_FALSE(manager.is_loaded<test_module_2>());
	EXPECT_FALSE(manager.is_loaded<test_module_3>());
}

TEST(module_manager, load_unregistered) {
	test_module_manager manager;
	try {
		manager.load<test_module_1>();
	} catch (const std::runtime_error& error) {
		EXPECT_EQ(error.what(), std::string("module not registered"));
	}
}

TEST(module_manager, unload_single) {
	test_module_manager manager;
	manager.register_module<test_module_1>();
	manager.register_module<test_module_2>();
	manager.register_module<test_module_3>();
	manager.load<test_module_3>();
	EXPECT_FALSE(manager.is_loaded<test_module_1>());
	EXPECT_FALSE(manager.is_loaded<test_module_2>());
	EXPECT_TRUE(manager.is_loaded<test_module_3>());
	manager.unload<test_module_3>();
}

TEST(module_manager, unload_unregistered) {
	test_module_manager manager;
	try {
		manager.unload<test_module_1>();
	} catch (const std::runtime_error& error) {
		EXPECT_EQ(error.what(), std::string("module not registered"));
	}
}
