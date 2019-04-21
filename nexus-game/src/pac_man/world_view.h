#pragma once

namespace pac_man {
struct world_view {
	void render(nx::window& window) {
		nx::shape::hexagon hex(50);
		hex.set_position(100, 100);
		hex.set_rotation(20);
		window.draw(hex);

	}
};
}  // namespace pac_man