#pragma once
#include "module_id.h"

namespace nexus {
template <class... arg_t>
struct module_dependency {
	static auto id() {
		return std::set<uint32_t>{module_id::get<arg_t>()...};
	}
};

struct no_dependency {};
template <>
struct module_dependency<no_dependency> {
	static auto id() {
		return std::set<uint32_t>{};
	}
};

}  // namespace nexus