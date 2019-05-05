#pragma once
#include <variant>

namespace pac_man::model {
enum class cell_content { large_dot, small_dot, cherry, wall };
struct cell {
	nx::vector2i m_position;
	std::optional<cell_content> m_item;
};
}  // namespace pac_man::model