#pragma once
#include "util.h"

namespace pac_man {
struct navgrid {
	struct cell {
		bool m_is_passable;
	};
	struct link {};

	navgrid(std::size_t width, std::size_t height)
		: m_width(width)
		, m_height(height) {
		m_cells.reserve(width * height);
		for (std::size_t y = 0; y < height; ++y) {
			for (std::size_t x = 0; x < width; ++x) {
				const bool is_border = x == 0 || y == 0 || x == width - 1 || y == height - 1;
				const bool is_center = x >= 2 && x <= width - 3 && y >= 2 && y <= height - 3;
				const bool is_even_row = y % 2 == 0;
				const bool is_even_col = x % 2 == 0;
				const bool passable = !is_border && !(is_center && is_even_col && is_even_row);
				m_cells.emplace_back<cell>({passable});
			}
		}
	}

	void draw(nexus::gfx::window& window) const {
		draw_grid(window, nexus::gfx::colors::gray, view::size);
		draw_dots(window, view::size);
	}

	void move(moving_entity& entity, const nexus::duration& duration) {
		const auto direction = entity.get_direction();
		if (can_move_in_direction(entity, direction)) {
			const auto distance = duration.to_seconds() * entity.get_speed();
			auto current = entity.get_position();
			switch (direction) {
				case pac_man::direction::right:
					current += nexus::vector2f{distance, 0};
					break;
				case pac_man::direction::down:
					current += nexus::vector2f{0, distance};
					break;
				case pac_man::direction::left:
					current += nexus::vector2f{-distance, 0};
					break;
				case pac_man::direction::up:
					current += nexus::vector2f{0, -distance};
					break;
			}
			entity.set_position(current);
		}
	}

private:
	bool has_reached_intersection(moving_entity& entity, direction dir) {
		
		
		return false;
	}

	bool can_move_in_direction(moving_entity& entity, direction dir) {
		nexus::vector2i current = entity.get_position() / view::grid_size;
		switch (dir) {
			case direction::left:
				return cell_is_passable(current + nexus::vector2i{-1, 0});
			case direction::right:
				return cell_is_passable(current + nexus::vector2i{1, 0});
			case direction::up:
				return cell_is_passable(current + nexus::vector2i{0, -1});
			case direction::down:
				return cell_is_passable(current + nexus::vector2i{0, 1});
		}
	}

	cell& get_cell(const position& pos) {
		return m_cells.at(pos.y * m_width + pos.x);
	}

	const cell& get_cell(const position& pos) const {
		return m_cells.at(pos.y * m_width + pos.x);
	}

	bool is_valid(const position& pos) const {
		return pos.x >= 0 && pos.x < m_width && pos.y >= 0 && pos.y < m_height;
	}

	bool cell_is_passable(const position& pos) const {
		return is_valid(pos) && get_cell(pos).m_is_passable;
	}

	bool can_change_direction(moving_entity& entity, direction dir) {
		const auto entity_pos = entity.get_position();
		const auto cell_index = nexus::vector2i{entity_pos.x / view::size.x, entity_pos.y / view::size.y};
		const auto cell_center = (cell_index * view::grid_size) + view::size / 2;
		const auto distance = entity_pos - cell_center;
		return sqrt(distance.x * distance.x + distance.y * distance.y) <= 2.0f;
	}

	void draw_grid(nexus::gfx::window& window, nexus::gfx::color color, nexus::vector2f cell_size) const {
		const nexus::vector2f grid_size{cell_size.x * m_width, cell_size.y * m_height};
		const auto line_width = 1;
		nexus::gfx::rect horizontal_line(line_width, grid_size.x);
		horizontal_line.set_fill_color(color);
		horizontal_line.set_rotation(-90);
		nexus::gfx::rect vertical_line(line_width, grid_size.y);
		vertical_line.set_fill_color(color);

		for (auto y = 0; y <= m_height; ++y) {
			horizontal_line.set_position({0, y * cell_size.y});
			window.draw(horizontal_line);
		}

		for (auto x = 0; x <= m_width; ++x) {
			vertical_line.set_position(x * cell_size.x, 0);
			window.draw(vertical_line);
		}
	}

	struct nav_dot : public nexus::gfx::circle {
		nav_dot(float size, nexus::gfx::color color)
			: nexus::gfx::circle(size) {
			set_origin({size, size});
			set_fill_color(color);
		}
	};

	void draw_dots(nexus::gfx::window& window, nexus::vector2f cell_size) const {
		auto cell_offset = cell_size / 2.f;
		auto passable = nav_dot(2, nexus::gfx::colors::green);
		auto blocked = nav_dot(8, nexus::gfx::colors::red);

		for (std::size_t y = 0; y < m_height; ++y) {
			for (std::size_t x = 0; x < m_width; ++x) {
				auto& cell = get_cell({x, y});
				auto& dot = cell.m_is_passable ? passable : blocked;
				const auto pos(cell_offset + nexus::vector2f{cell_size.x * x, cell_size.y * y});
				dot.set_position(pos);
				window.draw(dot);
			}
		}
	}

	std::vector<cell> m_cells;

	std::size_t m_width;
	std::size_t m_height;
};
}  // namespace pac_man