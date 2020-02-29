#pragma once
#include "game_data.h"
#include "entity_factory.h"
#include "player.h"

namespace pac_man {
struct game {
	game() {
		//m_entities.emplace_back(m_entity_factory.create());
	}

	bool is_running() const {
		return true;
	}

	void draw(nexus::gfx::window& window) {
		for (const auto& entity : m_entities) {
			entity->draw(window);
		}
	}
	void update(const nexus::duration& duration) {
		for (auto& entity : m_entities) {
			entity->update(duration);
		}
	}

private:	
	entity_factory m_entity_factory;
	std::vector<std::unique_ptr<entity>> m_entities;
	//std::unique_ptr<util::animation> m_anim;
};
}  // namespace pac_man