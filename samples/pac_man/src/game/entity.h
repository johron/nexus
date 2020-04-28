#pragma once
#include <array>
#include "game_data.h"
#include "../src/math/vector.h"

namespace pac_man {
struct entity {
	virtual ~entity() = default;

	virtual void update(const nexus::duration& /*duration*/) {}
	virtual void draw(nexus::gfx::window& /*window*/) = 0;
	virtual void set_position(const nexus::vector2f& position) {
		m_position = position;
	}
	virtual const nexus::vector2f& get_position() const {
		return m_position;
	}

protected:
	nexus::vector2f m_position;
};

struct direction_provider {
	virtual ~direction_provider() = default;
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
			return direction::none; 
		}
	}
};

struct speed_provider {
	virtual ~speed_provider() = default;
	virtual float get_speed() const = 0;
};

struct constant_speed_provider : public speed_provider {
	float get_speed() const override {
		return 120.f;
	}
};

using move_animations = std::array<nexus::gfx::sprite_animation, 4>;

struct moving_entity : public entity {
	moving_entity(std::unique_ptr<direction_provider> movement,
				  std::unique_ptr<speed_provider> speed,
				  move_animations sprites)
		: m_direction_provider(std::move(movement))
		, m_speed_provider(std::move(speed))
		, m_sprites(std::move(sprites)) {}

	void set_position(const nexus::vector2f& position) override {
		m_position = position;
		for (auto& sprite : m_sprites) {
			sprite.set_position(m_position);
		}
	}

	void update(const nexus::duration& duration) override {
		const auto direction = m_direction_provider->get_direction();
		const auto distance = m_speed_provider->get_speed() * duration.to_seconds();
		move(direction, distance);
	}

	void move(direction dir, float distance) {
		const auto index = static_cast<std::size_t>(dir);
		auto current_position = get_position();
		switch (dir) {
			case pac_man::direction::right:
				current_position += nexus::vector2f{distance, 0};
				break;
			case pac_man::direction::down:
				current_position += nexus::vector2f{0, distance};
				break;
			case pac_man::direction::left:
				current_position += nexus::vector2f{-distance, 0};
				break;
			case pac_man::direction::up:
				current_position += nexus::vector2f{0, -distance};
				break;
			case pac_man::direction::none:
				// don't move
				break;
		}
		set_position(current_position);
	}

	void draw(nexus::gfx::window& window) override {

	}

	std::unique_ptr<direction_provider> m_direction_provider;
	std::unique_ptr<speed_provider> m_speed_provider;
	move_animations m_sprites;
};

struct player : public moving_entity {
	static const data::entity type = data::entity::player;
	player(const move_animations& animations)
		: moving_entity(std::make_unique<keyboard_controller>(), std::make_unique<constant_speed_provider>(), animations) {}
};

}  // namespace pac_man