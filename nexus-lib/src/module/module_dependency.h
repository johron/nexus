#pragma once
#include "module_id.h"

namespace nexus {
template <class... arg_t>
struct module_dependency {
	static std::set<uint32_t> get() {
		return {module_id::get<arg_t>()...};
	}
};
struct no_dependency {};

template <>
struct module_dependency<no_dependency> {
	static std::set<uint32_t> get() {
		return {};
	}
};
}  // namespace nexus
