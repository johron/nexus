#pragma once
#include "entity_factory.h"
#include "player.h"

namespace pac_man {
struct game {
	game() {
		m_entities.emplace_back(m_entity_factory.create());
	}

	bool is_running() const {
		return true;
	}

	void draw(nexus::gfx::window& window) {
		for (const auto& entity : m_entities) {
			window.draw(*entity->m_sprite);
		}
	}
	void update() {}

private:	
	entity_factory m_entity_factory;
	std::vector<std::unique_ptr<entity>> m_entities;
};
}  // namespace pac_man