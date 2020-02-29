#pragma once
#include "../sfml/sprite.h"

namespace nexus::gfx {
struct sprite_animation : public sprite {
	sprite_animation(const nexus::gfx::image& image,
					 const std::vector<nexus::recti>& rects,
					 const nexus::duration& duration)
		: m_active_time(0)
		, m_total_time(duration)
		, m_previous_frame(0) {
		m_textures.reserve(rects.size());
		for (const auto& rect : rects) {
			m_textures.emplace_back(std::make_shared<nexus::gfx::texture>(image, rect));
		}
		set_texture(m_textures.front());
	}

	void update(const nexus::duration& delta_time) {
		m_active_time += delta_time;
		if (m_active_time >= m_total_time) {
			m_active_time %= m_total_time;
		}
		const auto percentage = static_cast<double>(m_active_time.count()) / m_total_time.count();
		const auto frame = static_cast<std::size_t>(percentage * m_textures.size());
		if (frame != m_previous_frame) {
			m_previous_frame = frame;
			set_texture(m_textures[frame]);
		}
	}

	std::vector<std::shared_ptr<nexus::gfx::texture>> m_textures;
	nexus::duration m_active_time;
	nexus::duration m_total_time;
	std::size_t m_previous_frame;
};
}