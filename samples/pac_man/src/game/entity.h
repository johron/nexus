#pragma once
#include <array>

namespace pac_man {
struct entity {
	virtual ~entity() = default;

	virtual void update(const nexus::duration& /*duration*/) {}
	virtual void draw(nexus::gfx::window& /*window*/) {}
};

struct direction_provider {
	virtual direction get_direction() const = 0;
};

struct keyboard_controller : public direction_provider {
	direction get_direction() const override {
		if (nexus::keyboard::is_key_down(nexus::keyboard::key::arrow_left)) {
			return direction::left;
		} else if (nexus::keyboard::is_key_down(nexus::keyboard::key::arrow_right)) {
			return direction::right;
		} else if (nexus::keyboard::is_key_down(nexus::keyboard::key::arrow_up)) {
			return direction::up;
		} else if (nexus::keyboard::is_key_down(nexus::keyboard::key::arrow_down)) {
			return direction::down;
		} else {
			throw std::runtime_error("unknown direction");
		}
	}
};

struct speed_provider {
	virtual float get_speed() const = 0;
};

struct constant_speed_provider : public speed_provider {
	float get_speed() const override {
		return 120.f;
	}
};

struct moving_entity : public entity {
	moving_entity(std::unique_ptr<direction_provider> movement,
				  std::unique_ptr<speed_provider> speed,
				  std::array<nexus::gfx::sprite_animation, 4> sprites)
		: m_direction_provider(std::move(movement))
		, m_speed_provider(std::move(speed))
		, m_sprites(std::move(sprites)) {}

	void update(const nexus::duration& duration) override {
		const auto direction = m_direction_provider->get_direction();
		const auto distance = m_speed_provider->get_speed() * duration.to_seconds();
		move(direction, distance);
	}

	void move(direction dir, float distance) {
		const auto index = static_cast<std::size_t>(dir);
		switch (dir) {
			case pac_man::direction::right:
				m_sprites[index].move({distance, 0});
				break;
			case pac_man::direction::down:
				m_sprites[index].move({0, distance});
				break;
			case pac_man::direction::left:
				m_sprites[index].move({-distance, 0});
				break;
			case pac_man::direction::up:
				m_sprites[index].move({0, -distance});
				break;
		}
	}

	std::unique_ptr<direction_provider> m_direction_provider;
	std::unique_ptr<speed_provider> m_speed_provider;
	std::array<nexus::gfx::sprite_animation, 4> m_sprites;
};
}  // namespace pac_man