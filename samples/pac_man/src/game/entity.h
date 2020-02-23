#pragma once

namespace pac_man {
enum class entity_type {
	pac_man
};

struct entity {
	entity(std::unique_ptr<nexus::gfx::sprite> sprite)
		: m_sprite(std::move(sprite)) {}
	virtual ~entity() = default;


	virtual void update(const nexus::duration& /*duration*/) {}

	std::unique_ptr<nexus::gfx::sprite> m_sprite;
};
}