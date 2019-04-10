#include <array>
#include <type_traits>
#include "../include/nexus/nexus.h"
#include "gtest/gtest.h"

using namespace nexus;
static constexpr auto the_update_time = std::chrono::milliseconds(20);

template <size_t tag>
struct test_module : public module {
	virtual void update() override {
		std::this_thread::sleep_for(the_update_time);
	}
};

using module_1 = test_module<1>;
using module_2 = test_module<2>;

struct module_3 : public test_module<3> {
	using dependencies = nexus::module_dependency<module_1, module_2>;
	module_3(int first, int second)
		: m_value(first + second) {
	}

	int m_value;
};

TEST(module_manager, module_id) {
	const auto id1 = util::type_id::get<module_1>();
	const auto id2 = util::type_id::get<module_2>();
	EXPECT_NE(id1, id2);
	EXPECT_EQ(id1, util::type_id::get<module_1>());
	const module_2 object;
	EXPECT_EQ(id2, util::type_id::get(object));
}

TEST(module_manager, register_module) {
	module_manager manager;
	manager.register_module<module_1>();
	manager.register_module<module_2>();
	manager.register_module<module_3>(1, 2);
}

TEST(module_manager, get_module) {
	module_manager manager;
	manager.register_module<module_1>();
	const auto& sample_module = manager.get<module_1>();
	static_assert(std::is_same_v<std::decay_t<decltype(sample_module)>, module_1>);
}

// TEST(module_manager, visit_sequential) {
// 	module_manager manager;
// 	manager.register_module<module_1>();
// 	manager.register_module<module_2>();
// 	const auto visitor = [](nexus::module& /*module*/) { /* do something */ };
// 	manager.visit(visitor);
// }

/*
TEST(module_manager, visit_parallel) {
	module_manager manager;
	manager.register_module<module_1>();
	manager.register_module<module_2>();

	struct update_visitor {
		void operator()(nexus::module& module) {
			module.update();
		}
	};
	const auto begin = std::chrono::steady_clock::now();
	manager.visit(update_visitor{}, std::execution::par);
	const auto duration = std::chrono::steady_clock::now() - begin;
	EXPECT_GE(duration, the_update_time);
	EXPECT_LE(duration, the_update_time * 2);
}*/


TEST(module_manager, load_single) {
	module_manager manager;
	manager.register_module<module_1>();
	manager.register_module<module_2>();
	manager.register_module<module_3>(1, 2);

	manager.load<module_1>();
	EXPECT_TRUE(manager.is_loaded<module_1>());
	EXPECT_FALSE(manager.is_loaded<module_2>());
	EXPECT_FALSE(manager.is_loaded<module_3>());
}

TEST(module_manager, load_dependencies) {
	module_manager manager;
	manager.register_module<module_1>();
	manager.register_module<module_2>();
	manager.register_module<module_3>(1, 2);

	// module 3 has dependencies to module 1 and 2, loading
	// it should result in all the modules being loaded
	manager.load<module_3>();
	EXPECT_TRUE(manager.is_loaded<module_1>());
	EXPECT_TRUE(manager.is_loaded<module_2>());
	EXPECT_TRUE(manager.is_loaded<module_3>());
}

TEST(module_manager, unload_single) {
	module_manager manager;
	manager.register_module<module_1>();
	manager.register_module<module_2>();
	manager.register_module<module_3>(1, 2);
	manager.load<module_3>();
	EXPECT_TRUE(manager.is_loaded<module_1>());
	EXPECT_TRUE(manager.is_loaded<module_2>());
	EXPECT_TRUE(manager.is_loaded<module_3>());
	// module 3 has a dependency to module 1, so unloading
	// module 1 should unload module 3 as well.
	manager.unload<module_1>();
}
