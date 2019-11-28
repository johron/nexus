#pragma once
#include "item.h"

namespace match_game::model {
struct cell {
	std::vector<item> m_items;
};

struct board {
	board(uint32_t width, uint32_t height)
		: m_width(width)
		, m_height(height) {}

	auto width() const { return m_width; }
	auto height() const { return m_height; }

	const cell& get_cell(nx::vector2u position) const {
		if (is_inside_bounds(position)) {
			return m_cells[position_to_index(position)];
		} else {
			throw std::runtime_error("out of bounds: attempting to access cell outside valid range");
		}
	}

	cell& get_cell(nx::vector2u position) {
		if (is_inside_bounds(position)) {
			return m_cells[position_to_index(position)];
		} else {
			throw std::runtime_error("out of bounds: attempting to access cell outside valid range");
		}
	}

private:
	bool is_inside_bounds(nx::vector2u position) const {
		return position.y < m_height && position.x < m_width;
	}
	std::size_t position_to_index(nx::vector2u position) const { return position.y * m_width + position.x; }

	std::vector<cell> m_cells;
	uint32_t m_width;
	uint32_t m_height;
};
}  // namespace match_game::model
