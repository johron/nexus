#pragma once
#include <type_traits>
#include "world_model.h"

namespace pac_man::view {
constexpr auto cell_view_size = 30;
constexpr auto cell_pos_size = 32;
constexpr auto grid_offset = nx::vector2f(10, 10);
struct cell {
	cell(const nx::vector2i& position, const nx::vector2f& offset)
		: m_shape(cell_view_size, cell_view_size) {
		m_shape.set_position(position * cell_pos_size + offset);
	}
	nx::shape::rect m_shape;
};

struct world {
	world(const model::world& model)
		: m_model(model) {
		m_cells.reserve(m_model.size().x * m_model.size().y);
		for (int y = 0; y < m_model.size().y; ++y) {
			for (int x = 0; x < m_model.size().x; ++x) {
				m_cells.emplace_back(cell({x, y}, grid_offset));
			}
		}
	}

	void render(nx::window& window) {
		for (const auto& cell : m_cells) {
			window.draw(cell.m_shape);
		}
	}

private:
	const model::world& m_model;
	std::vector<cell> m_cells;
};
}  // namespace pac_man::view
