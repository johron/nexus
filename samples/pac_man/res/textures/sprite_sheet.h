#pragma once

namespace pac_man::util {
struct sprite_sheet {
	struct sprite_data {
		nexus::vector2u position;
		nexus::vector2u size;
	};

	std::map<std::string, sprite_data> m_data = {{"ghost_red_right_1", {{4, 173}, {22, 22}}},
												 {"ghost_red_right_2", {{4, 173}, {22, 22}}}};
};
}  // namespace pac_man::util