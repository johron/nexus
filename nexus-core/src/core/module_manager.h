#pragma once
#include <execution>
#include <functional>
#include <map>
#include <typeindex>
#include <memory>

namespace nexus {
template <class module_t>
struct module_manager {
	template <class module_t, class alias_t = module_t, class... arg_t>
	void register_module(arg_t&&... args) {
		m_registry[std::type_index(typeid(alias_t))] = [args...]() {
			return module_entry{std::make_unique<module_t>(std::forward<arg_t>(args)...)};
		};
	}

	template <class module_t, class alias_t = module_t, class... arg_t>
	void insert_module(arg_t&&... args) {
		register_module<module_t, alias_t>(std::forward<arg_t>(args)...);
		load<alias_t>();
	}

	template <class module_t>
	[[nodiscard]] bool is_registered() const {
		return is_registered(std::type_index(typeid(module_t)));
	}

	template <class module_t>
	[[nodiscard]] bool is_loaded() const {
		return is_loaded(std::type_index(typeid(module_t)));
	}

	template <class module_t>
	module_t& get() {
		return static_cast<module_t&>(*m_modules.at(std::type_index(typeid(module_t))).m_module);
	}

	template <class module_t>
	const module_t& get() const {
		return static_cast<module_t&>(*m_modules.at(std::type_index(typeid(module_t))).m_module);
	}

	template <class module_t>
	void load() {
		load(std::type_index(typeid(module_t)));
	}

	template <class module_t>
	void unload() {
		unload(std::type_index(typeid(module_t)));
	}

	template <class functor_t>
	void visit(functor_t&& func) {
		std::for_each(
			m_modules.begin(), m_modules.end(), [&func](auto& entry) { func(*entry.second.m_module); });
	}

	template <class functor_t, class execution_policy_t>
	void visit(functor_t&& func, const execution_policy_t& policy) {
		std::for_each(policy, m_modules.begin(), m_modules.end(), [&func](auto& entry) {
			func(*entry.second.m_module);
		});
	}

private:
	[[nodiscard]] bool is_loaded(std::type_index id) const {
		return m_modules.find(id) != m_modules.end();
	}

	[[nodiscard]] bool is_registered(std::type_index id) const {
		return m_registry.find(id) != m_registry.end();
	}

	void load(std::type_index id) {
		if (!is_registered(id)) {
			throw std::runtime_error("module not registered");
		}

		if (!is_loaded(id)) {
			const auto& module_creator = m_registry.at(id);
			m_modules.insert(std::make_pair(id, module_creator()));
		}
	}

	void unload(std::type_index id) {
		if (!is_registered(id)) {
			throw std::runtime_error("module not registered");
		}

		if (is_loaded(id) && is_registered(id)) {
			m_modules.erase(id);
		}
	}

	struct module_entry {
		std::unique_ptr<module_t> m_module;
	};

	std::map<std::type_index, std::function<module_entry()>> m_registry;
	std::map<std::type_index, const module_entry> m_modules;
};
}  // namespace nexus