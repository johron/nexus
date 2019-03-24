#pragma once
#include "module.h"
#include "module_id.h"

namespace nexus {
struct module_manager {
	template <class module_t, class... arg_t>
	void register_module(arg_t... args) {
		const auto id = type_id::get<module_t>();
		m_modules[id] = std::make_unique<module_t>(std::forward<arg_t>(args)...);
	}

	template <class module_t>
	[[nodiscard]] bool is_registered() const {
		return m_modules.find(type_id::get<module_t>()) != m_modules.end();
	}

	template <class module_t>
	module_t& get() {
		return static_cast<module_t&>(*m_modules.at(type_id::get<module_t>()));
	}

	template <class module_t>
	const module_t& get() const {
		return static_cast<module_t&>(*m_modules.at(type_id::get<module_t>()));
	}

	template <class module_t>
	void load() {
	}

	void load(module_id id) {
	}

	template <class functor_t, class... arg_t>
	void visit(functor_t& func, arg_t... args) {
		for (auto& module : m_modules) {
			func(*module.second, std::forward<arg_t>(args)...);
		}
	}

private:
	std::map<uint32_t, std::unique_ptr<module>> m_modules;
};
}  // namespace nexus