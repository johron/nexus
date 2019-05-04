#pragma once

namespace pac_man {
struct cell {
	nx::vector2i m_pos;
};

struct world_model {
	world_model(nx::vector2i size)
		: m_size(size) {
		m_cells.reserve(size.x * size.y);
		for (int y = 0; y < size.y; ++y) {
			for (int x = 0; x < size.x; ++x) {
				m_cells.emplace_back(cell{nx::vector2i(x, y)});
			}
		}
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
}  // namespace pac_man