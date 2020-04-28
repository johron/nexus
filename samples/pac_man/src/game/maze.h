#pragma once
#include "entity.h"

namespace pac_man {
struct maze {
	maze(std::size_t width, std::size_t height)
		: m_width(width)
		, m_height(height) {}

	void update(const nexus::duration& duration) {
		for (auto& entity : m_entities) {
			entity->update(duration);
		}
	}

	void add_entity(std::unique_ptr<entity> entity) {
		m_entities.push_back(std::move(entity));
	}

	void draw(nexus::gfx::window& window) const {
		draw_grid(nexus::gfx::colors::red, window);

		for (const auto& entity : m_entities) {
			entity->draw(window);
		}
	}

	bool is_running() const {
		return true;
	}

	std::size_t width() const {
		return m_width;
	}

	std::size_t height() const {
		return m_height;
	}

private:
	void draw_grid(nexus::gfx::color color, nexus::gfx::window& window) const {
		const nexus::vector2f cell_size{22, 22};
		const nexus::vector2f grid_size{cell_size.x * width(), cell_size.y * height()};
		const auto line_width = 1;
		nexus::gfx::rect horizontal_line(line_width, grid_size.x);
		horizontal_line.set_fill_color(color);
		horizontal_line.set_rotation(-90);
		nexus::gfx::rect vertical_line(line_width, grid_size.y);
		vertical_line.set_fill_color(color);

		for (auto y = 0; y <= height(); ++y) {
			horizontal_line.set_position({0, y * cell_size.y});
			window.draw(horizontal_line);
		}

		for (auto x = 0; x <= width(); ++x) {
			vertical_line.set_position(x * cell_size.x, 0);
			window.draw(vertical_line);
		}
	}

	std::size_t m_width;
	std::size_t m_height;
	std::vector<std::unique_ptr<entity>> m_entities;
};
}  // namespace pac_man