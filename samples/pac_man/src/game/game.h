#pragma once
#include "maze.h"
#include "maze_factory.h"

namespace pac_man {
struct game {
	game(maze_factory& factory)
		: m_factory(factory)
		, m_maze(m_factory.make_maze()) {
	}

	bool is_running() const {
		return m_maze && m_maze->is_running();
	}

	void draw(nexus::gfx::window& window) {
		if (m_maze) {
			m_maze->draw(window);
		}
	}

	void update(const nexus::duration& duration) {
		if (m_maze) {
			m_maze->update(duration);
		}
	}

private:
	maze_factory& m_factory;
	std::unique_ptr<maze> m_maze;
};
}  // namespace pac_man