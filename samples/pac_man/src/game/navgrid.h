#pragma once

namespace pac_man {
struct navgrid {
	struct cell {};
	struct link {};

	navgrid(std::size_t width, std::size_t height)
		: m_width(width)
		, m_height(height) {}

	void draw(nexus::gfx::window& window) const {
		auto color = nexus::gfx::colors::red;
		const nexus::vector2f cell_size{22, 22};
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

		nexus::gfx::circle dot(4);
		dot.set_origin({4, 4});
		dot.set_fill_color(nexus::gfx::colors::green);
		for (std::size_t y = 0; y < m_height; ++y) {
			for (std::size_t x = 0; x < m_width; ++x) {
				const nexus::vector2f pos(cell_size.x * x, cell_size.y * y);
				dot.set_position(pos + nexus::vector2f{11, 11});
				window.draw(dot);
			}
		}
	}

private:
	std::vector<cell> m_cells;

	std::size_t m_width;
	std::size_t m_height;
};
}  // namespace pac_man