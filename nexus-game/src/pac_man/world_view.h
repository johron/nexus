#pragma once
#include "world_model.h"

namespace pac_man {
struct cell_view {
	cell_view(const cell& cell, nx::vector2f offset)
		: m_shape(30, 30) {
		m_shape.set_position(cell.m_pos * 32 + offset);
		m_shape.set_fill_color(nx::color(200, 0, 0, 70));
		m_shape.set_outline_color(nx::color(200, 80, 200));
	}

	nx::shape::rect m_shape;
};

struct world_view {
	world_view(const world_model& model)
		: m_model(model) {

		m_cells.reserve(model.cells().size());
		for (const auto& cell : model.cells()) {
			m_cells.emplace_back(cell, nx::vector2f{10, 10});
		}
	}

	void render(nx::window& window) {
		for (const auto& cell : m_cells) {
			window.draw(cell.m_shape);
		}
	}

private:
	const world_model& m_model;
	std::vector<cell_view> m_cells;
};
}  // namespace pac_man