#pragma once

namespace pac_man {
enum class entity_type {
	pac_man
};

struct entity {
	entity(std::unique_ptr<nexus::gfx::sprite> sprite)
		: m_sprite(std::move(sprite)) {}
	std::unique_ptr<nexus::gfx::sprite> m_sprite;
};
}