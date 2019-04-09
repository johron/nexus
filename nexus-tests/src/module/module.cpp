#include <array>
#include <type_traits>
#include "../include/nexus/nexus.h"
#include "gtest/gtest.h"

using namespace nexus;

struct module_1 : public module {
	virtual void update() override {
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
};
struct module_2 : public module {
	virtual void update() override {
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
};
struct module_3 : public module {
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

TEST(module_manager, visit_all) {
	module_manager manager;
	manager.register_module<module_1>();
	manager.register_module<module_2>();
	const auto visitor = [](auto&& /*module*/) { /* do something */ };
	manager.visit(visitor);
}

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

TEST(module_manager, visit_test) {
	module_manager manager;
	manager.register_module<module_1>();
	manager.register_module<module_2>();

	struct update_visitor {
		void operator()(nexus::module& module) {
			module.update();
		}
	};

	manager.visit(update_visitor{});
}
