#pragma once
#include "entity.h"
#include "navgrid.h"

namespace pac_man {
struct maze {
	maze(std::size_t width, std::size_t height)
		: m_width(width)
		, m_height(height) 
		, m_navgrid(width , height){
		for (std::size_t y = 0; y < height; ++y) {
			for (std::size_t x = 0; x < width; ++x) {
				m_cells.emplace_back();
			}
		}
	}

	void update(const nexus::duration& duration) {
		for (auto& entity : m_entities) {
			entity->update(duration);
		}

		move_entities(duration);
	}

	void move_entities(const nexus::duration& duration) {
		for (auto& entity : m_entities) {
			m_navgrid.move(*entity, duration);
		}
	}

	void add_entity(std::unique_ptr<moving_entity> entity, position pos) {
		entity->set_position({pos.x * view::size.x + view::size.x / 2, pos.y * view::size.y + view::size.y / 2});
		m_entities.push_back(std::move(entity));
	}

	void draw(nexus::gfx::window& window) const {
		m_navgrid.draw(window);

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
	struct cell {
		nexus::vector2u m_position;
	};
	std::vector<cell> m_cells;

	std::size_t m_width;
	std::size_t m_height;
	std::vector<std::unique_ptr<moving_entity>> m_entities;
	navgrid m_navgrid;
};
}  // namespace pac_man