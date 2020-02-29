#pragma once
#include "entity.h"

namespace pac_man {
struct player : public entity {
	player() {}

	nexus::vector2f get_movement(float speed, direction dir) {
		switch (dir) {
			case pac_man::direction::left:
				return {-speed, 0};
			case pac_man::direction::right:
				return {speed, 0};
			case pac_man::direction::up:
				return {0, -speed};
			case pac_man::direction::down:
				return {0, speed};
			default:
				return {};
		}
	}

	void update(const nexus::duration& /*duration*/) override {
// 		const auto speed = 120.f * duration.to_seconds();
// 		m_sprite->set_position(m_sprite->get_position() + get_movement(speed, get_direction()));
	}
};
}  // namespace pac_man