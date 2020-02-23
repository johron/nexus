#pragma once

namespace pac_man::util {
struct animation {
	animation(const nexus::gfx::image& image, const std::vector<nexus::recti>& rects) {
		m_textures.reserve(rects.size());
		for (const auto& rect : rects) {
			m_textures.emplace_back(std::make_shared<nexus::gfx::texture>(image, rect));
		}
		m_sprite = std::make_unique<nexus::gfx::sprite>(m_textures[0]);
	}

	void update(const nexus::duration& delta_time) {
		static float accumulated_time = 0.f;
		static std::size_t index = 0;
		accumulated_time += delta_time.to_seconds();
		if (accumulated_time >= 0.3f) {
			accumulated_time = 0.f;
			++index;
			if (index >= m_textures.size()) {
				index = 0;
			}
			m_sprite->set_texture(m_textures[index]);
		}
	}

	void draw(nexus::gfx::window& window) {
		window.draw(*m_sprite);
	}

	std::vector<std::shared_ptr<nexus::gfx::texture>> m_textures;
	std::unique_ptr<nexus::gfx::sprite> m_sprite;
};
}  // namespace pac_man::util