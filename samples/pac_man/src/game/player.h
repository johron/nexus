#pragma once
#include "entity.h"

namespace pac_man {
enum class direction { none, left, right, up, down };
struct player : public entity {
	player(std::unique_ptr<nexus::gfx::sprite> sprite)
		: entity(std::move(sprite)) {}

	direction get_direction() const {
		if (nexus::keyboard::is_key_down(nexus::keyboard::key::arrow_left)) {
			return direction::left;
		} else if (nexus::keyboard::is_key_down(nexus::keyboard::key::arrow_right)) {
			return direction::right;
		} else if (nexus::keyboard::is_key_down(nexus::keyboard::key::arrow_up)) {
			return direction::up;
		} else if (nexus::keyboard::is_key_down(nexus::keyboard::key::arrow_down)) {
			return direction::down;
		} else {
			return direction::none;
		}
	}

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
			case pac_man::direction::none:
			default:
				return {};
		}
	}

	void update(const nexus::duration& duration) override {
		const auto speed = 120.f * duration.to_seconds();
		m_sprite->set_position(m_sprite->get_position() + get_movement(speed, get_direction()));
	}
};
}  // namespace pac_man