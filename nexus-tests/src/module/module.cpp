#include <type_traits>
#include "../include/nexus/nexus.h"
#include "gtest/gtest.h"

struct module_1 : public nexus::module {};
struct module_3 : public nexus::module {};

template <class... type>
struct type_list {};

template <class T>
struct deps {
	static std::vector<nexus::module_id> get() {
		return {};
	}
};

template <>
struct deps<module_3> {
	static std::vector<nexus::module_id> get() {
		return {nexus::type_id::get<module_1>()};
	}
};

struct module_2 : public nexus::module {
	module_2(int first, int second)
		: m_value(first + second) {
	}

	int m_value;
};

TEST(module_manager, type_id) {
	const auto id1 = nexus::type_id::get<module_1>();
	const auto id2 = nexus::type_id::get<module_2>();
	EXPECT_NE(id1, id2);
	EXPECT_EQ(id1, nexus::type_id::get<module_1>());
	const module_2 object(1, 2);
	EXPECT_EQ(id2, nexus::type_id::get(object));
}

TEST(module_manager, register_module) {
	nexus::module_manager manager;
	manager.register_module<module_1>();
	manager.register_module<module_2>(1, 2);
}

TEST(module_manager, get_module) {
	nexus::module_manager manager;
	manager.register_module<module_1>();
	const auto& sample_module = manager.get<module_1>();
	static_assert(std::is_same_v<std::decay_t<decltype(sample_module)>, module_1>);
}

TEST(module_manager, visit) {
	nexus::module_manager manager;
	manager.register_module<module_1>();
	manager.register_module<module_2>(1, 2);
	const auto visitor = [](auto&& /*module*/) { /* do something */ };
	manager.visit(visitor);
}

TEST(module_manager, module_dependencies) {
	nexus::module_manager manager;
	manager.register_module<module_1>();
	manager.register_module<module_2>(1, 2);
	manager.register_module<module_3>();

	manager.load<module_3>();
}