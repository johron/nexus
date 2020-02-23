#pragma once
#include "player.h"
#include "../util/animation.h"

namespace pac_man {
struct entity_factory {
	entity_factory() 
		: m_sprite_sheet(std::make_unique<nexus::gfx::image>("res/textures/sprite_sheet.png")) {
	}

	std::unique_ptr<entity> create() {
		auto sprite = std::make_unique<nexus::gfx::sprite>(
			std::make_unique<nexus::gfx::texture>(*m_sprite_sheet, nexus::recti{292, 173, 22, 22}));
		return std::make_unique<player>(std::move(sprite));
	}

	std::unique_ptr<util::animation> create_anim() {
		return std::make_unique<util::animation>(
			*m_sprite_sheet,
			std::vector<nexus::recti>{nexus::recti{292, 173, 22, 22}, nexus::recti{340, 173, 22, 22}},
			std::chrono::milliseconds(300));
	}

	std::unique_ptr<nexus::gfx::image> m_sprite_sheet;
};
}  // namespace pac_man