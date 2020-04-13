#pragma once
#include "maze.h"
namespace pac_man {
struct game {
	game()
		: m_maze(std::make_unique<maze>(20, 20))
		, m_view(std::make_unique<maze_view>(*m_maze)) {}

	bool is_running() const {
		return true;
	}

	void draw(nexus::gfx::window& window) {
		if (m_view) {
			m_view->draw(window);
		}
	}

	void update(const nexus::duration& duration) {
		if (m_maze) {
			m_maze->update(duration);
		}
	}

private:
	std::unique_ptr<maze> m_maze;
	std::unique_ptr<maze_view> m_view;
};
}  // namespace pac_man