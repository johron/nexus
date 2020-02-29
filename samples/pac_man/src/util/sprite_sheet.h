#pragma once
#include "../game/game_data.h"

namespace pac_man::util {
struct sprite_sheet {
	sprite_sheet(const std::string& filename)
		: m_image(filename) {}

	auto make_animation(direction facing, nexus::vector2i origin, uint8_t frames) {
		const nexus::vector2i stride{24, 0};
		const nexus::vector2i size{22, 22};
		const nexus::vector2i first_frame = origin + (stride * static_cast<int32_t>(facing) * 2);

		std::vector<nexus::recti> rects;
		rects.reserve(frames);
		for (auto i = 0; i < frames; ++i) {
			const auto pos = first_frame + stride * i;
			rects.emplace_back(pos.x, pos.y, size.x, size.y);
		}

		return std::make_unique<nexus::gfx::sprite_animation>(m_image, rects, std::chrono::milliseconds(300));
	}

	auto make_animation(data::entity entity, direction facing) {
		switch (entity) {
			case pac_man::data::entity::player:
				return make_animation(facing, {0, 0}, 2);
			case pac_man::data::entity::blinky:
				return make_animation(facing, {0, 24}, 2);
			case pac_man::data::entity::inky:
				return make_animation(facing, {0, 48}, 2);
			case pac_man::data::entity::pinky:
				return make_animation(facing, {0, 72}, 2);
			case pac_man::data::entity::clyde:
				return make_animation(facing, {0, 96}, 2);
			default:
				throw std::runtime_error("unknown animation");
		}
	}

private:
	nexus::gfx::image m_image;
};
}  