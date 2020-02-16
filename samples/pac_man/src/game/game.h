#pragma once
#include "../src/sfml/window.h"

namespace pac_man {
struct game {
	bool is_running() const {
		return true;
	}

	void draw(nexus::gfx::window& /*window*/) {}
	void update() {}
};
}  // namespace pac_man