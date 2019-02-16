#pragma once
#include "sfml/sfml_window.h"

namespace nexus {
auto make_window(uint32_t width, uint32_t height, std::string&& title) {
	return std::make_unique<sfml::window>(width, height, std::move(title));
}
}  // namespace nexus