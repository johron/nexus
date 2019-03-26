#pragma once
#include "module.h"
#include "module_id.h"

namespace nexus {
struct module_manager {
	template <class module_t, class... arg_t>
	void register_module(arg_t... args) {
		const auto id = module_id::get<module_t>();
		m_modules[id] = std::make_unique<module_t>(std::forward<arg_t>(args)...);
	}

	template <class module_t>
	[[nodiscard]] bool is_registered() const {
		return m_modules.find(module_id::get<module_t>()) != m_modules.end();
	}

	template <class module_t>
	module_t& get() {
		return static_cast<module_t&>(*m_modules.at(module_id::get<module_t>()));
	}

	template <class module_t>
	const module_t& get() const {
		return static_cast<module_t&>(*m_modules.at(module_id::get<module_t>()));
	}

	template <class module_t>
	void load() {
		const auto id = module_id::get<module_t>();
		if (is_registered<module_t>() && !is_loaded<module_t>()) {
			load(typename module_t::dependencies{});

			auto& module = m_modules.at(id);
			if (module->on_load() == module::load_result::ok) {
				m_loaded.insert(id);
			} else {
				throw std::runtime_error("failed to load module:" + std::to_string(id));
			}
		}

	}

	template <class module_t>
	[[nodiscard]] bool is_loaded() const {
		return m_loaded.find(module_id::get<module_t>()) != m_loaded.end();
	}

	template <class functor_t, class... arg_t>
	void visit(functor_t& func, arg_t... args) {
		for (auto& module : m_modules) {
			func(*module.second, std::forward<arg_t>(args)...);
		}
	}

private:
	template <class... module_t>
	void load(const module_dependency<module_t...>& /*unused*/) {
		[[maybe_unused]] int unused[] = {0, (load<module_t>(), 0)...};
	}

	template <>
	void load(const module_dependency<no_dependency>&) {
		/* do nothing */
	}

	std::map<uint32_t, std::unique_ptr<module>> m_modules;
	std::set<uint32_t> m_loaded;
};
}  // namespace nexus