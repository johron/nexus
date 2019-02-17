#pragma once
#include "ghost.h"
#include "player.h"

namespace game {
struct maze {
	maze() {
		for (uint16_t y = 0; y < 29; ++y) {
			for (uint16_t x = 0; x < 26; ++x) {
				m_cells.emplace_back(cell{x, y, true});
			}
		}
	}

	struct cell {
		uint16_t x;
		uint16_t y;
		bool can_pass;
	};

	void update() {
		m_player.update();
		for (auto& ghost : m_ghosts) {
			ghost.update();
		}
	}

	void render(nexus::window& window) const {
		sf::RectangleShape r(sf::Vector2f(22, 22));
		r.setOutlineColor(sf::Color::Blue);
		r.setOutlineThickness(.6f);
		const sf::Vector2f offset(50.f, 50.f);
		for (const auto& cell : m_cells) {
			if (cell.can_pass) {
				r.setFillColor(cell.can_pass ? sf::Color(0, 150, 0, 100) : sf::Color(150, 0, 0, 100));
				r.setPosition(offset + sf::Vector2f{cell.x * 22.0f, cell.y * 22.0f});
				window.draw(r);

				// render passable
			} else {
				// render blocked
			}
		}

		m_player.render();
		for (const auto& ghost : m_ghosts) {
			ghost.render();
		}
	}

private:
	std::vector<cell> m_cells;
	std::vector<ghost> m_ghosts;
	player m_player;
};
}  // namespace game