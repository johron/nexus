#pragma once
#include "../model/board.h"

namespace match_game::view {
// struct board {
// 	board(const model::board& model)
// 		: m_model(model) {}
// 
// 	void render(nx::window& window) {
// 		const float cell_size = 64;
// 		const nx::vector2f offset(20, 20);
// 		for (uint32_t y = 0; y < m_model.height(); ++y) {
// 			for (uint32_t x = 0; x < m_model.width(); ++x) {
// 				nx::shape::rect r(60.f, 60.f);
// 				r.set_position(offset + nx::vector2f{x * cell_size, y * cell_size});
// 				r.set_fill_color({0, 0, 0, 0});
// 				r.set_outline_color({150, 0, 0});
// 				r.set_outline_thickness(2);
// 				window.draw(r);
// 			}
// 		}
// 	}
// 
// private:
// 	const model::board& m_model;
// };
}  // namespace match_game::view