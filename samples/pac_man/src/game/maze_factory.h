#pragma once
#include "maze.h"
#include "entity_factory.h"

namespace pac_man {
struct maze_factory {
	maze_factory(entity_factory& entity_factory)
		: m_entity_factory(entity_factory) {}

	std::unique_ptr<maze> make_maze() {
		auto new_maze = std::make_unique<maze>(21, 21);
		new_maze->add_entity(m_entity_factory.create(data::entity::player), {1, 1});

		return new_maze;
	}

private:
	entity_factory& m_entity_factory;
};
}  // namespace pac_man