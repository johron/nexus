#pragma once
#include "module.h"
#include "module_id.h"

namespace nexus {
struct module_manager {
	template <class module_t, class... arg_t>
	void register_module(arg_t... args) {
		const auto id = module_id::get<module_t>();
		m_modules.insert(std::make_pair(id,
										entry{std::make_unique<module_t>(std::forward<arg_t>(args)...),
											  module_t::dependencies::get(),
											  id}));
	}

	template <class module_t>
	[[nodiscard]] bool is_registered() const {
		return is_registered(module_id::get<module_t>());
	}

	template <class module_t>
	[[nodiscard]] bool is_loaded() const {
		return is_loaded(module_id::get<module_t>());
	}

	template <class module_t>
	module_t& get() {
		return static_cast<module_t&>(*m_modules.at(module_id::get<module_t>()).m_module);
	}

	template <class module_t>
	const module_t& get() const {
		return static_cast<module_t&>(*m_modules.at(module_id::get<module_t>()).m_module);
	}

	template <class module_t>
	void load() {
		load(module_id::get<module_t>());
	}

	template <class module_t>
	void unload() {
		unload(module_id::get<module_t>());
	}

	template <class functor_t, class... arg_t>
	void visit(functor_t& func, arg_t... args) {
		for (auto& module : m_modules) {
			func(*module.second.m_module, std::forward<arg_t>(args)...);
		}
	}

	template <class visitor_t>
	auto visit(visitor_t&& visitor) {
		return visitor(m_modules);
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
			auto& entry = m_modules.at(id);
			for (auto& dependency : entry.m_dependencies) {
				load(dependency);
			}

			if (entry.m_module->on_load() == module::load_result::ok) {
				m_loaded.insert(id);
			} else {
				throw std::runtime_error("failed to load module " + std::to_string(id));
			}
		}
	}

	void unload(uint32_t current) {
		if (is_loaded(current) && is_registered(current)) {
			for (const auto loaded_module : m_loaded) {
				if (loaded_module != current) {
					const auto& dependencies = m_modules.at(loaded_module).m_dependencies;
					const bool dependency_is_about_to_unload = dependencies.find(current) != dependencies.end();
					if (dependency_is_about_to_unload) {
						unload(loaded_module);
					}
				}
			}

			auto& entry = m_modules.at(current);
			if (entry.m_module->on_unload() == module::load_result::ok) {
				m_loaded.erase(current);
			} else {
				throw std::runtime_error("failed to unload module " + std::to_string(current));
			}
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