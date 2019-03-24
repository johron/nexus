#pragma once

namespace nexus {
struct module {
	module(const module& other) = delete;
	module& operator=(const module& other) = delete;

	module() = default;
	~module() = default;
};
}  // namespace nexus