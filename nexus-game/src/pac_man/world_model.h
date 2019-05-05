#pragma once
#include "world_cell.h"

namespace pac_man::model {
struct world {
	world(std::vector<cell>&& cells, const nx::vector2i& size)
		: m_cells(std::forward<std::vector<cell>>(cells))
		, m_size(size) {
	}

	void update(const nx::time& /*delta_time*/) {
	}

	const std::vector<cell>& cells() const {
		return m_cells;
	}

	const nx::vector2i& size() const {
		return m_size;
	}

private:
	std::vector<cell> m_cells;
	nx::vector2i m_size;
};
}  // namespace pac_man::model