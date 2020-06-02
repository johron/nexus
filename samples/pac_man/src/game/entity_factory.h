#pragma once
#include <functional>

#include "entity.h"
#include "sprite_sheet.h"

namespace pac_man {
struct entity_factory {
	using create_func = std::function<std::unique_ptr<entity>()>;
	entity_factory(sprite_sheet&& sprites)
		: m_sprites(std::forward<sprite_sheet>(sprites)) {
		register_entity<player>(player::type, get_animations(player::type));
	}

	template <class entity_t, class... arg_t>
	void register_entity(data::entity entity_type, arg_t... args) {
		auto func = [args...]() { return std::make_unique<entity_t>(args...); };
		m_creators.insert({entity_type, func});
	}

	std::unique_ptr<entity> create(data::entity type) {
		auto entity = m_creators.at(type)();
		return entity;
	}

private:
	move_animations get_animations(data::entity type) {
		return {m_sprites.make_animation(type, direction::right),
				m_sprites.make_animation(type, direction::down),
				m_sprites.make_animation(type, direction::left),
				m_sprites.make_animation(type, direction::up)};
	}

	std::map<data::entity, create_func> m_creators;
	sprite_sheet m_sprites;
};
}  // namespace pac_man