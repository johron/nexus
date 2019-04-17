#pragma once
#include "../engine/parallel.h"
#include "module.h"

namespace nexus {
struct module_manager {
	template <class module_t, class alias_t = module_t, class... arg_t>
	void register_module(arg_t&&... args) {
		const auto id = util::type_id::get<alias_t>();
		m_registry[id] = [args...]() { return module_entry{std::make_unique<module_t>(args...)}; };
	}

	template <class module_t, class alias_t = module_t, class... arg_t>
	void add_module(arg_t&&... args) {
		register_module<module_t, alias_t>(std::forward<arg_t>(args)...);
		load<alias_t>();
	}

	template <class module_t>
	[[nodiscard]] bool is_registered() const {
		return is_registered(util::type_id::get<module_t>());
	}

	template <class module_t>
	[[nodiscard]] bool is_loaded() const {
		return is_loaded(util::type_id::get<module_t>());
	}

	template <class module_t>
	module_t& get() {
		return static_cast<module_t&>(*m_modules.at(util::type_id::get<module_t>()).m_module);
	}

	template <class module_t>
	const module_t& get() const {
		return static_cast<module_t&>(*m_modules.at(util::type_id::get<module_t>()).m_module);
	}

	template <class module_t>
	void load() {
		load(util::type_id::get<module_t>());
	}

	template <class module_t>
	void unload() {
		unload(util::type_id::get<module_t>());
	}

	template <class functor_t>
	void visit(functor_t&& func) {
		visit(std::forward<functor_t>(func), parallel::execute_sequential);
	}

	template <class functor_t, class execution_policy>
	void visit(functor_t&& func, const execution_policy& policy) {
		parallel::for_each(policy, begin(m_modules), end(m_modules), [&func](const auto& current) {
			func(*current.second.m_module);
		});
	}

private:
	[[nodiscard]] bool is_loaded(uint32_t id) const {
		return m_modules.find(id) != m_modules.end();
	}

	[[nodiscard]] bool is_registered(uint32_t id) const {
		return m_registry.find(id) != m_registry.end();
	}

	void load(uint32_t id) {
		if (!is_registered(id)) {
			throw std::runtime_error("module not registered");
		}

		if (!is_loaded(id)) {
			const auto& module_creator = m_registry.at(id);
			m_modules.insert(std::make_pair(id, module_creator()));
		}
	}

	void unload(uint32_t id) {
		if (!is_registered(id)) {
			throw std::runtime_error("module not registered");
		}

		if (is_loaded(id) && is_registered(id)) {
			m_modules.erase(id);
		}
	}

	struct module_entry {
		std::unique_ptr<module> m_module;
	};

	std::map<uint32_t, std::function<module_entry()>> m_registry;
	std::map<uint32_t, const module_entry> m_modules;
};
}  // namespace nexus