#pragma once
#include "sfml/engine.h"

namespace nexus {

auto make_engine(uint32_t width, uint32_t height, std::string&& title) {
	return std::make_unique<sfml::engine>(width, height, std::move(title));
}


}  // namespace nexus