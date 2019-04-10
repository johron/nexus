#pragma once
#include <algorithm>

//#include <execution>
#include <future>
#include <iterator>
#include "module.h"

namespace nexus {
struct module_manager {
	template <class module_t, class... arg_t>
	void register_module(arg_t... args) {
		const auto id = util::type_id::get<module_t>();
		m_modules.insert(std::make_pair(id,
										entry{std::make_unique<module_t>(std::forward<arg_t>(args)...),
											  module_t::dependencies::get(),
											  id}));
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
		visit(func/*, std::execution::seq*/);
		std::for_each(/*policy,*/ begin(m_modules), end(m_modules), [&func](const auto& current) {
			func(*current.second.m_module);
		});
	}

	template <class functor_t, class execution_policy>
	void visit(functor_t&& func, const execution_policy& /*policy*/) {
		std::for_each(/*policy,*/ begin(m_modules), end(m_modules), [&func](const auto& current) {
			func(*current.second.m_module);
		});
	}

private:
	[[nodiscard]] bool is_loaded(uint32_t id) const {
		return m_loaded.find(id) != m_loaded.end();
	}

	[[nodiscard]] bool is_registered(uint32_t id) const {
		return m_modules.find(id) != m_modules.end();
	}

	void load(uint32_t id) {
		if (!is_loaded(id) && is_registered(id)) {
			auto& module = m_modules.at(id);
			for (auto& dependency : module.m_dependencies) {
				load(dependency);
			}

			if (module.m_module->on_load() == module::load_result::ok) {
				m_loaded.insert(id);
			} else {
				throw std::runtime_error("failed to load module " + std::to_string(id));
			}
		}
	}

	void unload(uint32_t id) {
		if (is_loaded(id) && is_registered(id)) {
			unload_dependencies(id);

			auto& module = m_modules.at(id);
			if (module.m_module->on_unload() == module::load_result::ok) {
				m_loaded.erase(id);
			} else {
				throw std::runtime_error("failed to unload module " + std::to_string(id));
			}
		}
	}

	void unload_dependencies(uint32_t id) {
		std::set<uint32_t> to_unload;
		const auto is_dependency = [this, id](uint32_t type_id) {
			if (type_id != id) {
				const auto& dependencies = m_modules.at(type_id).m_dependencies;
				return dependencies.find(id) != dependencies.end();
			} else {
				return false;
			}
		};

		std::copy_if(
			m_loaded.begin(), m_loaded.end(), std::inserter(to_unload, to_unload.end()), is_dependency);
		for (const auto& module : to_unload) {
			unload(module);
		}
	}

	struct entry {
		std::unique_ptr<module> m_module;
		std::set<uint32_t> m_dependencies;
		uint32_t m_id;
	};

	std::map<uint32_t, const entry> m_modules;
	std::set<uint32_t> m_loaded;
};
}  // namespace nexus