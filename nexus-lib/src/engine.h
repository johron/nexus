#pragma once

#include "SFML/Graphics.hpp"

namespace nexus {
	struct engine {};

	auto make_engine() {
		return engine{};
	}
}