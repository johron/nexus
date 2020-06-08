#pragma once
#include "../src/math/vector.h"
#include "game_data.h"

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
	virtual void update() = 0;
	virtual direction get_direction() const = 0;
};

struct keyboard_controller : public direction_provider {
	keyboard_controller()
		: m_direction(direction::left) {}

	void update() override {
		if (nexus::keyboard::is_key_down(nexus::keyboard::key::arrow_right)) {
			m_direction = direction::right;
		} 
		if (nexus::keyboard::is_key_down(nexus::keyboard::key::arrow_up)) {
			m_direction = direction::up;
		} 
		if (nexus::keyboard::is_key_down(nexus::keyboard::key::arrow_down)) {
			m_direction = direction::down;
		} 
		if (nexus::keyboard::is_key_down(nexus::keyboard::key::arrow_left)) {
			m_direction = direction::left;
		}
	}

	direction get_direction() const override {
		return m_direction;
	}

private:
	direction m_direction;
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
	moving_entity(std::unique_ptr<direction_provider> movement, std::unique_ptr<speed_provider> speed, move_animations sprites)
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
		m_direction_provider->update();
		for (auto& sprite : m_sprites) {
			sprite.update(duration);
		}
	}

	auto get_speed() const {
		return m_speed_provider->get_speed();
	}

	auto get_direction() const {
		return m_direction_provider->get_direction();
	}

	void draw(nexus::gfx::window& window) override {
		const auto direction = get_direction();
		const auto& sprite = m_sprites.at(static_cast<std::size_t>(direction));
		window.draw(sprite, sf::BlendAdd);
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