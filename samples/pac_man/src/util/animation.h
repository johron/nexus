#pragma once

namespace pac_man::util {
struct animation {
	animation(const nexus::gfx::image& image, const std::vector<nexus::recti>& rects, const nexus::duration& duration) 
		: m_active_time(0)
		, m_total_time(duration) 
		, m_last_frame(0) {
		m_textures.reserve(rects.size());
		for (const auto& rect : rects) {
			m_textures.emplace_back(std::make_shared<nexus::gfx::texture>(image, rect));
		}
		m_sprite = std::make_unique<nexus::gfx::sprite>(m_textures[0]);
	}

	void update(const nexus::duration& delta_time) {
		m_active_time += delta_time;
		if (m_active_time >= m_total_time) {
			m_active_time %= m_total_time;
		}
		const auto percentage = static_cast<double>(m_active_time.count()) / m_total_time.count(); 
		const auto frame = static_cast<std::size_t>(percentage * m_textures.size());
		if (frame != m_last_frame) {
			m_last_frame = frame;
			m_sprite->set_texture(m_textures[frame]);
		}
	}

	void draw(nexus::gfx::window& window) {
		window.draw(*m_sprite);
	}

	std::vector<std::shared_ptr<nexus::gfx::texture>> m_textures;
	std::unique_ptr<nexus::gfx::sprite> m_sprite;
	nexus::duration m_active_time;
	nexus::duration m_total_time;
	std::size_t m_last_frame;
};
}  // namespace pac_man::util