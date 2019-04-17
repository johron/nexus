#include "../include/nexus/nexus.h"
#include "gtest/gtest.h"

using namespace nexus;
static constexpr auto the_update_time = std::chrono::milliseconds(10);

template <size_t tag>
struct test_module : public module {
	virtual void update() override {
		std::this_thread::sleep_for(the_update_time);
	}
};

using module_1 = test_module<1>;
using module_2 = test_module<2>;

struct module_3 : public test_module<3> {
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
	EXPECT_FALSE(manager.is_loaded<module_1>());
	EXPECT_TRUE(manager.is_registered<module_1>());
}

TEST(module_manager, add_module) {
	module_manager manager;
	manager.add_module<module_1>();
	EXPECT_TRUE(manager.is_loaded<module_1>());
	EXPECT_TRUE(manager.is_registered<module_1>());
}

struct interface_type : public module {
	virtual int number() const = 0;
};

struct implementing_type : public interface_type {
	implementing_type(int number)
		: m_number(number) {
	}

	int number() const override {
		return m_number;
	}

private:
	int m_number;
};

TEST(module_manager, module_alias) {
	module_manager manager;
	manager.add_module<implementing_type, interface_type>(10);
	auto& sample = manager.get<interface_type>();
	EXPECT_EQ(sample.number(), 10);
}

TEST(module_manager, get_module) {
	module_manager manager;
	manager.register_module<module_1>();
	manager.load<module_1>();
	const auto& sample_module = manager.get<module_1>();
	static_assert(std::is_same_v<std::decay_t<decltype(sample_module)>, module_1>);
}

TEST(module_manager, visit_sequential) {
	module_manager manager;
	manager.register_module<module_1>();
	manager.register_module<module_2>();
	const auto visitor = [](nexus::module& /*module*/) { /* do something */ };
	manager.visit(visitor);
}

TEST(module_manager, visit_parallel) {
	module_manager manager;
	manager.register_module<module_1>();
	manager.register_module<module_2>();

	struct update_visitor {
		void operator()(nexus::module& module) {
			module.update();
		}
	};
	manager.visit(update_visitor{}, parallel::execute_parallel);
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

TEST(module_manager, load_unregistered) {
	module_manager manager;
	try {
		manager.load<module_1>();
	} catch (const std::runtime_error& error) {
		EXPECT_EQ(error.what(), std::string("module not registered"));
	}
}

TEST(module_manager, unload_single) {
	module_manager manager;
	manager.register_module<module_1>();
	manager.register_module<module_2>();
	manager.register_module<module_3>(1, 2);
	manager.load<module_3>();
	EXPECT_FALSE(manager.is_loaded<module_1>());
	EXPECT_FALSE(manager.is_loaded<module_2>());
	EXPECT_TRUE(manager.is_loaded<module_3>());
	manager.unload<module_3>();
}

TEST(module_manager, unload_unregistered) {
	module_manager manager;
	try {
		manager.unload<module_1>();
	} catch (const std::runtime_error& error) {
		EXPECT_EQ(error.what(), std::string("module not registered"));
	}
}