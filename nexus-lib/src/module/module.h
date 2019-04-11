#pragma once
#include "module_dependency.h"

namespace nexus {
struct module {
	using dependencies = module_dependency<no_dependency>;

	module(const module& other) = delete;
	module& operator=(const module& other) = delete;

	module() = default;
	virtual ~module() = default;

	enum class load_result { ok, error };

	virtual load_result on_load() {
		return load_result::ok;
	}
	virtual load_result on_unload() {
		return load_result::ok;
	}

	virtual void update() {
	}
};
}  // namespace nexus